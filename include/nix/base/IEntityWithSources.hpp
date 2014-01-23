// Copyright (c) 2013, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#ifndef NIX_I_ENTITY_WITH_SOURCES_H
#define NIX_I_ENTITY_WITH_SOURCES_H

#include <string>
#include <vector>

#include <nix/base/IEntityWithMetadata.hpp>

namespace nix {

class Source;

namespace base {

/**
 * Base class for entities that are associated with sources.
 */
class IEntityWithSources : virtual public IEntityWithMetadata {

public:

    /**
     * Get the number of sources associated with this entity.
     *
     * @return The number sources.
     */
    virtual size_t sourceCount() const = 0;

    /**
     * Checks if a specific source is associated with this entity.
     *
     * @param source      The source to check.
     *
     * @return True if the source is associated with this entity, false otherwise.
     */
    //virtual bool hasSource(const Source &source) const = 0;

    /**
     * Checks if a specific source is associated with this entity.
     *
     * @param id      The source id to check.
     *
     * @return True if the source is associated with this entity, false otherwise.
     */
    virtual bool hasSource(const std::string &id) const = 0;

    /**
     * Add a specific source to the list of associated sources.
     *
     * @param source      The source to associate with this entity.
     */
    virtual void addSource(const Source &source) = 0;

    /**
     * Remove a source from the list of associated sources.
     * This source will not be deleted from the file.
     *
     * @param source      The source to remove.
     *
     * @return True if the source was removed, false otherwise.
     */
    virtual bool removeSource(const std::string &id) = 0;

    /**
     * Set all sources associated with this entity. All previously
     * associated sources, that are not in the vector will be removed.
     *
     * @param sources     A vector with all sources.
     */
    virtual void sources(const std::vector<Source> &sources) = 0;

    /**
     * Get all associated sources of this entity.
     *
     * @return A vector with all sources.
     */
    virtual std::vector<Source> sources() const = 0;

    /**
     * Returns the source identified by the given id.
     *
     * @param string the source id
     */
    virtual Source getSource(const std::string &id) const = 0;

};


} // namespace base
} // namespace nix

#endif // NIX_I_ENTITY_WITH_SOURCES_H