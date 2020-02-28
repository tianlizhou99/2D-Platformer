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
			auto money4 = std::make_shared<CMoney>(&game, moneyImage);
			money4->SetLocation(1000, 10);
			money4->SetWorth(1000);

			// Create president objects
			auto president1 = std::make_shared<CPresident>(&game, presImage);
			president1->SetLocation(250, 10);
			auto president2 = std::make_shared<CPresident>(&game, presImage);
			president2->SetLocation(550, 10);
			auto president3 = std::make_shared<CPresident>(&game, presImage);
			president3->SetLocation(850, 10);

			// Force player to collide with money
			player->SetLocation(100, 10);
			money1->Collision(player.get());

			// Check if score updates properly
			double score = game.GetScore();
			Assert::IsTrue(score == 100);

			// Force player to collide with president
			player->SetLocation(250, 10);
			president1->Collision(player.get());
			money2->Update(0);
			money3->Update(0);
			money4->Update(0);

			// Force player to collide with money
			player->SetLocation(400, 10);
			money2->Collision(player.get());

			// Check if tuition Increased
			score = scoreboard->GetScore();
			Assert::IsTrue(score == 210);

			// Force player to collide with president, again
			player->SetLocation(550, 10);
			president2->Collision(player.get());
			money3->Update(0);
			money4->Update(0);

			// Force player to collide with money
			player->SetLocation(700, 10);
			money3->Collision(player.get());

			// Check if tuition Increased
			score = scoreboard->GetScore();
			Assert::IsTrue(score == 331);

			// Force player to collide with president, once more
			player->SetLocation(850, 10);
			president3->Collision(player.get());
			money4->Update(0);

			// Force player to collide with money
			player->SetLocation(1000, 10);
			money4->Collision(player.get());

			// Check if tuition Increased
			score = scoreboard->GetScore();
			Assert::IsTrue(score == 1662);
		}

		TEST_METHOD(TestCScoreboardExtraItemCollisions)
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


			// Create president objects
			auto president1 = std::make_shared<CPresident>(&game, presImage);
			president1->SetLocation(250, 10);


			// Force player to collide with money twice
			player->SetLocation(100, 10);
			money1->Collision(player.get());
			money1->SetLocation(100, 10);
			money1->Collision(player.get());

			// Check if score updates properly
			double score = game.GetScore();
			Assert::IsTrue(score == 100);

			// Force player to collide with president twice
			player->SetLocation(250, 10);
			president1->Collision(player.get());
			money2->Update(0);			
			president1->SetLocation(250, 10);
			president1->Collision(player.get());
			money2->Update(0);


			// Force player to collide with money
			player->SetLocation(400, 10);
			money2->Collision(player.get());

			// Check if tuition Increased
			score = scoreboard->GetScore();
			Assert::IsTrue(score == 210);
		}
	};
}