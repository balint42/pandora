// Copyright (c) 2013, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.


#include <nix.hpp>
#include <nix/hdf5/FileHDF5.hpp>

using namespace std;

namespace nix {


File File::open(const std::string name, FileMode mode, Implementation impl) {
    if (impl == Implementation::Hdf5) {
        return File(std::make_shared<hdf5::FileHDF5>(name, mode));
    } else {
        throw runtime_error("Unknown implementation!");
    }
}


vector<Section> File::findSections(util::Filter<Section>::type filter, size_t max_depth) const {

    vector<Section> results;

    vector<Section> roots = sections();
    for (auto root : roots) {
        vector<Section> secs = root.findSections(filter, max_depth);
        results.insert(results.end(), secs.begin(), secs.end());
    }

    return results;
}

valid::Result File::validate() const {
    valid::Result result = valid::validate(std::initializer_list<valid::condition> {
        valid::could(*this, &File::isOpen, valid::notFalse(), {
            valid::must(*this, &File::createdAt, valid::notFalse(), "date is not set!"),
            valid::should(*this, &File::version, valid::notEmpty(), "version is not set!"),
            valid::should(*this, &File::format, valid::notEmpty(), "format is not set!"),
            valid::should(*this, &File::location, valid::notEmpty(), "location is not set!") })
    });
        
    // now get all entities from the file: use the multi-getter for each type of entity
    // (the multi-getters use size_t-getter which in the end use H5Lget_name_by_idx
    // to get each file objects name - the count is determined by H5::Group::getNumObjs
    // so that in the end really all file objects are retrieved)
    
    // Blocks
    auto blcks = blocks();
    for(auto &block : blcks) {
        result.concat(block.validate());
        // DataArrays
        auto data_arrays = block.dataArrays();
        for(auto &data_array : data_arrays) {
            result.concat(data_array.validate());
            // Dimensions
            auto dims = data_array.dimensions();
            for(auto &dim : dims) {
                if(dim.dimensionType() == DimensionType::Range) {
                    auto d = dim.asRangeDimension();
                    result.concat(d.validate());
                }
                if(dim.dimensionType() == DimensionType::Set) {
                    auto d = dim.asSetDimension();
                    result.concat(d.validate());
                }
                if(dim.dimensionType() == DimensionType::Sample) {
                    auto d = dim.asSampledDimension();
                    result.concat(d.validate());
                }
            }
        }
        // DataTags
        auto data_tags = block.dataTags();
        for(auto &data_tag : data_tags) {
            result.concat(data_tag.validate());
            // Features
            auto features = data_tag.features();
            for(auto &feature : features) {
                result.concat(feature.validate());
            }
        }
        // SimpleTags
        auto simple_tags = block.simpleTags();
        for(auto &simple_tag : simple_tags) {
            result.concat(simple_tag.validate());
            // Features
            auto features = simple_tag.features();
            for(auto &feature : features) {
                result.concat(feature.validate());
            }
        }
        // Sources
        auto sources = block.findSources();
        for(auto &source : sources) {
            result.concat(source.validate());
        }
    }
    // Sections
    auto sections = findSections();
    for(auto &section : sections) {
        result.concat(section.validate());
        // Properties
        auto props = section.properties();
        for(auto &prop : props) {
            result.concat(prop.validate());
        }
    }

    return result;
}

}
