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
			midplatform->SetLocation(768, 944);
			game2.Add(leftplatform);
			game2.Add(rightplatform);
			game2.Add(midplatform);

			Assert::IsTrue(game1.GetEntities().size() == 3);

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
			auto topwall = make_shared<CWall>(&game2);
			topwall->SetLocation(768, 942 - 30);
			auto midwall = make_shared<CWall>(&game2);
			midwall->SetLocation(768, 942);
			auto bottomwall = make_shared<CWall>(&game2);
			bottomwall->SetLocation(768, 942 + 30);
			auto ttomwall = make_shared<CWall>(&game2);
			ttomwall->SetLocation(768, 942 + 60);
			game2.AddFront(topwall);
			game2.AddFront(midwall);
			game2.AddFront(bottomwall);
			game2.AddFront(ttomwall);

			Assert::IsTrue(game1.GetEntities().size() == 4);

			for (int i = 0; i < 3; i++)
			{
				Assert::IsTrue((game1.GetEntities()[i])->GetX() == (game2.GetEntities()[i])->GetX());
				Assert::IsTrue((game1.GetEntities()[i])->GetY() == (game2.GetEntities()[i])->GetY());
			}
		}

		TEST_METHOD(GameStateTest)
		{
			CGame game;

			game.SetTimer(0);
			Assert::IsTrue(game.GetState() == 0);

			game.SetTimer(5.6);
			Assert::IsTrue(game.GetState() == 1);
		}

		TEST_METHOD(LoadLevelTest)
		{
			CGame game;
			CGame* game_ptr = &game;

			Assert::IsTrue(game.GetLevelHeight() == 0);

			game.Load(L"levels/level0.xml");

			Assert::IsTrue(game.GetLevelHeight() == 1024);

		}

	};
}