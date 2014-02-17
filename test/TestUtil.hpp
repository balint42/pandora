// Copyright (c) 2013, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#include <iostream>
#include <sstream>
#include <iterator>
#include <stdexcept>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

#include <nix.hpp>
#include <nix/util/util.hpp>


class TestUtil: public CPPUNIT_NS::TestFixture {
private:

    CPPUNIT_TEST_SUITE(TestUtil);
    CPPUNIT_TEST(testUnitScaling);
    CPPUNIT_TEST(testIsSIUnit);
    CPPUNIT_TEST(testSIUnitSplit);
    CPPUNIT_TEST(testIsCompoundSIUnit);
    CPPUNIT_TEST(testSplitCompoundUnit);
    CPPUNIT_TEST_SUITE_END ();

public:

    void testUnitScaling();
    void testIsSIUnit();
    void testSIUnitSplit();
    void testIsCompoundSIUnit();
    void testSplitCompoundUnit();
};
