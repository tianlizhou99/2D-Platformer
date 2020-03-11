#include "pch.h"
#include "CppUnitTest.h"
#include "Timer.h"
#include "Game.h"
#include <memory>
#include "Element.h"
#include "Entity.h"
#include "XmlNode.h"
#include "player.h"
#include "character.h"
#include "badger.h"
#include "wolverine.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Gdiplus;

namespace Testing
{
	TEST_CLASS(CCharacterTest)
	{
	public:
		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}


		TEST_METHOD(TestNothing)
		{
			// This is an empty test just to ensure the system is working
		}


		TEST_METHOD(PlayerMoveTest)
		{
			CGame game;
			auto player = std::make_shared<CPlayer>(&game);
			game.Add(player);

			player->SetLocation(0, 500);
			player->SetVelX(10);
			double elapsed = 0;
			player->Update(elapsed);
			Assert::IsTrue(player->GetX() > 500);

			player->SetLocation(0, 500);
			player->SetVelX(-10);
			elapsed = 0;
			player->Update(elapsed);
			Assert::IsTrue(player->GetX() < 500);
		}

		TEST_METHOD(VillianMoveTest)
		{
			CGame game;
			/// add the Player to the game
			auto badger = std::make_shared<CBadger>(&game);

			badger->SetLocation(500, 500);

			Assert::IsTrue(badger->GetX() == 500);

			Assert::IsTrue(badger->GetY() == 500);
			badger->Update(1);
			Assert::IsTrue(badger->GetX() == 500);
			Assert::IsTrue(badger->GetY() > 500);

		}
		TEST_METHOD(ElapsedTest)
		{
			CGame game;
			auto player = std::make_shared<CPlayer>(&game);
			game.Add(player);

			player->SetLocation(500, 500);
			player->SetVelY(-750);
			double elapsed = 0;
			player->Update(elapsed);
			Assert::IsTrue(player->GetY() == 500);

			elapsed = .5;
			player->Update(elapsed);
			Assert::IsTrue(player->GetVelY() == -375);
		}
	};
}
