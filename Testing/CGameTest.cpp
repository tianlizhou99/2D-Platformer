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
			game1.LoadPlatform(L"images/snowLeft.png", L"images/snowMid.png", L"images/snowRight.png", 768, 944, 96, 32);

			CGame game2;
			auto leftplatform = make_shared<CPlatform>(&game2, L"images/snowLeft.png");
			leftplatform->SetLocation(768 - 32, 944);
			auto rightplatform = make_shared<CPlatform>(&game2, L"images/snowRight.png");
			rightplatform->SetLocation(768 + 32, 944);
			auto midplatform = make_shared<CPlatform>(&game2, L"images/snowMid.png");
			midplatform->SetLocation(768, 944);
			game2.Add(leftplatform);
			game2.Add(rightplatform);
			game2.Add(midplatform);

		}

		TEST_METHOD(LoadWallTest)
		{
			CGame game1;
			game1.LoadWall(L"images/wall1.png", 768, 944, 96, 32);

			CGame game2;
			wstring wallImage = L"images/wall1.png";
			auto wall = make_shared<CWall>(&game2, wallImage);
			wall->SetLocation(768, 944);
			game2.Add(wall);
		}



	};
}