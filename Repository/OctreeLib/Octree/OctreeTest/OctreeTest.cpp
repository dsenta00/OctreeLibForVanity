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
        Pos3 CENTER_AXIS = Pos3{
            0.0f,
            0.0f,
            0.0f
        };
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

            for each (var result in results)
            {
                Assert::IsNull(Repository::get(result));
            }

            for each (var result in results)
            {
                std::string persistedName = Repository::create("object");
                std::cout << persistedName << std::endl;
                Assert::AreEqual(persistedName, result);
            }

            for each (var result in results)
            {
                Octree *octree = Repository::get(result);

                Assert::IsNotNull(octree);
                Assert::IsTrue(octree->empty());
                Assert::IsNull(octree->getRoot());
                Assert::IsTrue(memcmp(&octree->averagePoint(), &CENTER_AXIS, sizeof(Pos3)) == 0);
                Assert::IsNull(octree->findNearest(CENTER_AXIS));
            }
        }

        TEST_METHOD(TestCreateAndInsertVertex)
        {
            var persistedName = Repository::create("object");
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

            for (var vertex : vertices)
            {
                OctreeLeaf *nearestPos = octree->findNearest(vertex.position);

                if (octree->empty())
                {
                    Assert::IsNull(nearestPos);
                }
                else
                {
                    Assert::IsNotNull(nearestPos);
                }

                Logger::WriteMessage(std::string("\t-> Persisting vertex ")
                                     .append(Pos3Handler::toString(&vertex.position))
                                     .append(" to octree \"")
                                     .append(persistedName)
                                     .append("\" and closest point (so far in the same octree) is ")
                                     .append((nearestPos == nullptr) ? "(null)" : nearestPos->toString())
                                     .append(" ... \n").c_str());

                Repository::addVertex(persistedName, &vertex);
            }
        }


        TEST_METHOD(TestObjectCollision)
        {
            var cubeName = Repository::create("cube");
            Octree *cube = Repository::get(cubeName);
            Assert::IsNotNull(cube);

            var triangleName = Repository::create("triangle");
            Octree *triangle = Repository::get(triangleName);
            Assert::IsNotNull(triangle);

            Logger::WriteMessage("Check if EMPTY cube does not collide with a EMPTY triangle!");
            Assert::IsFalse(cube->collidesWith(*triangle));
            Assert::IsFalse(triangle->collidesWith(*cube));

            // ------- CUBE ------- 
            std::vector<Vertex> cubeVertices = {
                { Pos3{ 0, 0, 0 } },
                { Pos3{ 1, 0, 0 } },
                { Pos3{ 1, 1, 0 } },
                { Pos3{ 0, 1, 0 } },
                { Pos3{ 0, 1, 1 } },
                { Pos3{ 1, 1, 1 } },
                { Pos3{ 1, 0, 1 } },
                { Pos3{ 0, 0, 1 } }
            };

            for (var vertex : cubeVertices)
            {
                Repository::addVertex(cubeName, &vertex);
            }

            Logger::WriteMessage("Check if cube does not collide with a EMPTY triangle!");
            Assert::IsFalse(cube->collidesWith(*triangle));
            Assert::IsFalse(triangle->collidesWith(*cube));

            // ------- TRIANGLE ------- 
            std::vector<Vertex> triangleVertices = {
                { Pos3{ 0, 0, 0 } },
                { Pos3{ 1, 0, 0 } },
                { Pos3{ 1, 1, 0 } }
            };

            for (var vertex : triangleVertices)
            {
                Repository::addVertex(triangleName, &vertex);
            }

            Logger::WriteMessage(std::to_string(cube->getCount()).c_str());
            Logger::WriteMessage(std::to_string(triangle->getCount()).c_str());

            Logger::WriteMessage("Check if triangle collides with a cube!");
            Assert::IsTrue(triangle->collidesWith(*cube));

            Logger::WriteMessage("Check if cube collides with a triangle!");
            Assert::IsTrue(cube->collidesWith(*triangle));

            // ------- TRIANGLE FAR AWAY ------- 
            var anotherTriangleName = Repository::create("triangle");
            Octree *anotherTriangle = Repository::get(anotherTriangleName);
            Assert::IsNotNull(anotherTriangle);

            std::vector<Vertex> anotherTriangleVertices = {
                { Pos3{ 12, 12, 12 } },
                { Pos3{ 13, 12, 12 } },
                { Pos3{ 13, 13, 12 } }
            };

            for (var vertex : anotherTriangleVertices)
            {
                Repository::addVertex(anotherTriangleName, &vertex);
            }

            Logger::WriteMessage("Check if cube does not collide with another triangle!");
            Assert::IsFalse(cube->collidesWith(*anotherTriangle));
            Assert::IsFalse(anotherTriangle->collidesWith(*cube));
        };
    };
};