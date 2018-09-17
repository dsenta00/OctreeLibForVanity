#include "targetver.h"
#include "CppUnitTest.h"
#include "..\..\..\Repository.h"
#include "..\Pos3Handler.h"
#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OctreeTest
{		
    TEST_CLASS(OctreeTest)
	{
        Pos3 CENTER_AXIS = Pos3{ 0.0f, 0.0f, 0.0f };
	public:
		
        /**
         * Test create and get objects.
         */
		TEST_METHOD(TestCreateAndGet)
		{

            std::string results[4] = {
                "object",
                "object (1)",
                "object (2)", 
                "object (3)",
            };

            for each (std::string &result in results)
            {
                Assert::IsNull(Repository::get(result));
            }

            for each (std::string &result in results)
            {
                std::string persistedName = Repository::create("object");
                std::cout << persistedName << std::endl;
                Assert::AreEqual(persistedName, result);
            }

            for each (std::string &result in results)
            {
                Octree *octree = Repository::get(result);

                Assert::IsNotNull(octree);
                Assert::AreEqual(octree->getCount(), (size_t)0);
                Assert::IsNull(octree->getRoot());
                Assert::IsTrue(memcmp(&octree->averagePoint(), &CENTER_AXIS, sizeof(Pos3)) == 0);
                Assert::IsNull(octree->findNearest(CENTER_AXIS));
            }
		}

        TEST_METHOD(TestCreateAndInsertVertex)
        {
            std::string persistedName = Repository::create("object");
            Octree *octree = Repository::get(persistedName);

            Assert::IsNotNull(octree);

            std::vector<Vertex> vertices = {
                { Pos3{ 0.0f, 1.0f, 2.0f } },
                { Pos3{ 0.0f, 2.0f, 1.0f } },
                { Pos3{ 1.0f, 0.0f, 2.0f } },
                { Pos3{ 1.0f, 2.0f, 0.0f } },
                { Pos3{ 2.0f, 1.0f, 0.0f } },
                { Pos3{ 2.0f, 0.0f, 1.0f } }
            };

            for (auto &vertex : vertices)
            {
                OctreeLeaf *nearestPos = octree->findNearest(vertex.position);

                if (octree->getCount() == 0)
                {
                    Assert::IsNull(nearestPos);
                }
                else
                {
                    Assert::IsNotNull(nearestPos);
                }

                std::cout << std::string("\t -- A lambda: -> Persisting vertex ")
                              .append(Pos3Handler::toString(&vertex.position))
                              .append(" to octree ")
                              .append(persistedName)
                              .append(" and closest point (so far in the same octree) is ")
                              .append(nearestPos == nullptr ? "(null)" : nearestPos->toString())
                              .append(" ... \n") << std::endl;

                Repository::addVertex(persistedName, &vertex);
            }
        }
	};
}