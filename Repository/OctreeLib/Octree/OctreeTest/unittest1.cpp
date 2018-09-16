#include "targetver.h"
#include "CppUnitTest.h"
#include <string>
#include "..\..\..\Repository.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Repository;

namespace OctreeTest
{		
    TEST_CLASS(OctreeTest)
	{
	public:
		
		TEST_METHOD(TestCreateAndGet)
		{
            std::string results[4] = {
                "object",
                "object (1)",
                "object (2)", 
                "object (3)",
            };

            for each (std::string result in results)
            {
                Assert::IsNull(get(result));
            }

            for each (std::string result in results)
            {
                Assert::AreEqual(create("object"), result);
            }

            for each (std::string result in results)
            {
                Assert::IsNotNull(get(result));
            }
		}
	};
}