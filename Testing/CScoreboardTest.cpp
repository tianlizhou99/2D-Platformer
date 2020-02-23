#include "pch.h"
#include "CppUnitTest.h"
#include "Scoreboard.h"
#include "Game.h"
#include <memory>
#include "Element.h"
#include "Entity.h"
#include "XmlNode.h"
#include "player.h"
#include <President.h>
#include <Money.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Gdiplus;

namespace Testing
{
	TEST_CLASS(CScoreboardTest)
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

		TEST_METHOD(TestScoreboardGetterSetters)
		{
			CGame game;

			Assert::IsTrue(game.GetScore() == 0);

			/// add the scoreboard to the game
			auto scoreboard = std::make_shared<CScoreboard>(&game);

			double score = scoreboard->GetScore();

			Assert::IsTrue(score == 0);

			game.SetScore(100);

			Assert::IsTrue(game.GetScore() == 100);

			game.SetScore(1000);

			Assert::IsTrue(game.GetScore() == 1000);
		}

		TEST_METHOD(TestCScoreboardTuitionIncrease)
		{
			CGame game;
			/// Add the scoreboard to the game
			auto scoreboard = std::make_shared<CScoreboard>(&game);
			auto player = std::make_shared<CPlayer>(&game);

			// Initialize files
			wstring presImage = L"images/stanley.png";
			wstring moneyImage = L"images/money100.png";


			// Create money objects
			auto money1 = std::make_shared<CMoney>(&game, moneyImage);
			money1->SetLocation(100, 10);
			money1->SetWorth(100);
			auto money2 = std::make_shared<CMoney>(&game, moneyImage);
			money2->SetLocation(400, 10);
			money2->SetWorth(100);
			auto money3 = std::make_shared<CMoney>(&game, moneyImage);
			money3->SetLocation(700, 10);
			money3->SetWorth(100);

			// Force player to collide with money
			player->SetLocation(100, 10);
			game.CollisionTest(player.get());

			// Check if score updates properly
			double score = game.GetScore();
			Assert::IsTrue(score == 100);

			// Force player to collide with president
			auto president1 = std::make_shared<CPresident>(&game, presImage);
			president1->SetLocation(100, 10);
			game.CollisionTest(player.get());

			// Force player to collide with money
			player->SetLocation(400, 10);
			game.CollisionTest(player.get());

			// Check if tuition Increased
			score = scoreboard->GetScore();
			Assert::IsTrue(score == 210);

			// Force player to collide with president, again
			auto president2 = std::make_shared<CPresident>(&game, presImage);
			president2->SetLocation(400, 10);
			game.CollisionTest(player.get());

			// Force player to collide with money
			player->SetLocation(700, 10);
			game.CollisionTest(player.get());

			// Check if tuition Increased
			score = scoreboard->GetScore();
			Assert::IsTrue(score == 331);
		}
	};
}