#include "pch.h"
#include "CppUnitTest.h"
#include "Platform.h"
#include "Wall.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CGameTest)
	{
	public:
		
		TEST_METHOD(LoadPlatformTest)
		{
			CGame game1;
			game1.LoadPlatform(L"", L"", L"", 768, 944, 96, 32);

			CGame game2;
			auto leftplatform = make_shared<CPlatform>(&game2, L"");
			leftplatform->SetLocation(768 - 32, 944);
			auto rightplatform = make_shared<CPlatform>(&game2, L"");
			rightplatform->SetLocation(768 + 32, 944);
			auto midplatform = make_shared<CPlatform>(&game2, L"");
			midplatform->SetLocation(768-2, 944);
			game2.Add(leftplatform);
			game2.Add(rightplatform);
			game2.Add(midplatform);

			Assert::IsTrue(game2.GetEntities().size() == 3);

			for (int i = 0; i < 3; i++)
			{
				Assert::IsTrue((game1.GetEntities()[i])->GetX() == (game2.GetEntities()[i])->GetX());
				Assert::IsTrue((game1.GetEntities()[i])->GetY() == (game2.GetEntities()[i])->GetY());
			}
		}

		TEST_METHOD(LoadWallTest)
		{
			CGame game1;
			game1.LoadWall(L"", 768, 944, 32, 96);

			CGame game2;
			auto topwall = make_shared<CPlatform>(&game2, L"");
			topwall->SetLocation(768, 944 - 32);
			auto midwall = make_shared<CPlatform>(&game2, L"");
			midwall->SetLocation(768, 944);
			auto bottomwall = make_shared<CPlatform>(&game2, L"");
			bottomwall->SetLocation(768, 944 + 32);
			game2.Add(topwall);
			game2.Add(midwall);
			game2.Add(bottomwall);

			Assert::IsTrue(game2.GetEntities().size() == 3);

			for (int i = 0; i < 2; i++)
			{
				Assert::IsTrue((game1.GetEntities()[i])->GetX() == (game2.GetEntities()[i])->GetX());
				Assert::IsTrue((game1.GetEntities()[i])->GetY() == (game2.GetEntities()[i])->GetY());
			}
		}

		

	};
}