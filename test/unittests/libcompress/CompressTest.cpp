/**
 * @CopyRight:
 * FISCO-BCOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FISCO-BCOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FISCO-BCOS.  If not, see <http://www.gnu.org/licenses/>
 * (c) 2016-2018 fisco-dev contributors.
 *
 * @brief: UT for SnappyCompress
 *
 * @file CompressTest.cpp
 * @author: yujiechen
 * @date 2019-03-21
 */

#include <libcompress/SnappyCompress.h>
#include <libdevcore/CommonData.h>
#include <test/tools/libutils/TestOutputHelper.h>
#include <boost/test/unit_test.hpp>
#include <iostream>

using namespace dev;
using namespace dev::compress;
namespace dev
{
namespace test
{
BOOST_FIXTURE_TEST_SUITE(CompressTest, TestOutputHelperFixture)

class CompressTestFixture
{
public:
    void checkCompressAlgorithm(std::string algorithm)
    {
        size_t dataLenFields = 0;
        if (algorithm == "snappy")
        {
            m_compressHandler = std::make_shared<SnappyCompress>();
        }

        std::string inputData = "abc21324";
        bytes compressedData;
        bytes inputDataBytes(inputData.begin(), inputData.end());

        /// compress test
        size_t compressLen = m_compressHandler->compress(ref(inputDataBytes), compressedData);
        BOOST_CHECK((compressLen + dataLenFields) == compressedData.size());

        /// uncompress test
        bytes uncompressData;
        size_t uncompressLen = m_compressHandler->uncompress(ref(compressedData), uncompressData);
        BOOST_CHECK(uncompressData.size() == uncompressLen);
        BOOST_CHECK(toHex(uncompressData) == toHex(inputDataBytes));
        BOOST_CHECK(asString(uncompressData) == inputData);
    }

private:
    std::shared_ptr<CompressInterface> m_compressHandler;
};

BOOST_AUTO_TEST_CASE(testCompressAlgorithm)
{
    CompressTestFixture compressFixture;
    compressFixture.checkCompressAlgorithm("snappy");
}
BOOST_AUTO_TEST_SUITE_END()
}  // namespace test
}  // namespace dev
