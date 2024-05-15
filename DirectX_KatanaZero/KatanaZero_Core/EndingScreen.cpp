#include "PreCompile.h"
#include "EndingScreen.h"

AEndingScreen::AEndingScreen()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	BackGround = CreateDefaultSubObject<USpriteRenderer>("BackGround");
	BackGround->SetSprite(ImgRes::ending_background);
	BackGround->SetOrder(ERenderOrder::BackGround);
	BackGround->SetAutoSize(2.0f, true);
	BackGround->SetupAttachment(Root);

	Smoke = CreateDefaultSubObject<USpriteRenderer>("Smoke");
	Smoke->CreateAnimation(Anim::ending_smoke, ImgRes::ending_smoke, 0.16f, true);
	Smoke->ChangeAnimation(Anim::ending_smoke);
	Smoke->SetOrder(ERenderOrder::MapComponent_Back);
	Smoke->SetAutoSize(2.0f, true);
	Smoke->SetupAttachment(Root);
	Smoke->SetPosition({ -16.0f, 64.0f, 0.0f });

	AllTide.reserve(TideNum);
	float TideScaleX = 170.0f;
	for (int i = 0; i < TideNum; i++)
	{
		AllTide.push_back(CreateDefaultSubObject<USpriteRenderer>("Tide"));
		AllTide[i]->CreateAnimation(Anim::ending_tide, ImgRes::ending_tide, 0.12f, true);
		AllTide[i]->ChangeAnimation(Anim::ending_tide);
		AllTide[i]->SetOrder(ERenderOrder::MapComponent_Back);
		AllTide[i]->SetAutoSize(2.0f, true);
		AllTide[i]->SetupAttachment(Root);
		AllTide[i]->SetPosition({ -600.0f + TideScaleX * i, -275.0f, 0.0f });
	}

	Title = CreateDefaultSubObject<USpriteRenderer>("Title");
	Title->SetSprite(ImgRes::ending_title);
	Title->SetOrder(ERenderOrder::EffectBack);
	Title->SetAutoSize(2.0f, true);
	Title->SetupAttachment(Root);
	Title->SetPosition({ 0.0f, 180.0f, 0.0f });
	Title->SetActive(false);

	SetRoot(Root);
}

AEndingScreen::~AEndingScreen()
{
}

void AEndingScreen::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
}

void AEndingScreen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AEndingScreen::StateInit()
{
	// State Create
	State.CreateState(EndingScrenState::none);
	State.CreateState(EndingScrenState::fade_in);
	State.CreateState(EndingScrenState::ending_credit);
	State.CreateState(EndingScrenState::fade_out);

	// State Start
	State.SetStartFunction(EndingScrenState::none, [=] {});
	State.SetStartFunction(EndingScrenState::fade_in, [=]
		{
			AllMulColor = 0.0f;
			float4 StartMulColor = { 0.0f, 0.0f, 0.0f, 1.0f };
			SetScreenMulColor(StartMulColor);
			IsFade = true;
		}
	);

	State.SetStartFunction(EndingScrenState::ending_credit, [=] 
		{
			AllMulColor = 0.0f;
			float4 StartMulColor = { 1.0f, 1.0f, 1.0f, AllMulColor };
			Title->SetMulColor(StartMulColor);
			Title->SetActive(true);
			IsFade = true;
			EndingOrder = 0;
		}
	);

	State.SetStartFunction(EndingScrenState::fade_out, [=] 
		{
			AllMulColor = 1.0f;
			float4 StartMulColor = { AllMulColor, AllMulColor, AllMulColor, 1.0f };
			SetScreenMulColor(StartMulColor);
			IsFade = true;
		}
	);

	// State Update
	State.SetUpdateFunction(EndingScrenState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(EndingScrenState::fade_in, [=](float _DeltaTime)
		{
			if (true == IsFade)
			{
				float4 MulColor = float4::One;
				AllMulColor += 0.2f * _DeltaTime;
				if (1.0f < AllMulColor)
				{
					IsFade = false;
					AllMulColor = 1.0f;
					SetScreenMulColor(MulColor);
					State.ChangeState(EndingScrenState::ending_credit);
					return;
				}

				MulColor.R = AllMulColor;
				MulColor.G = AllMulColor;
				MulColor.B = AllMulColor;
				SetScreenMulColor(MulColor);
			}
		}
	);

	State.SetUpdateFunction(EndingScrenState::ending_credit, [=](float _DeltaTime)
		{
			switch (EndingOrder)
			{
			case 0:
				EndingUpdate(_DeltaTime);
				break;
			case 1:
				EndingUpdate1(_DeltaTime);
				break;
			default:
				break;
			}
		}
	);

	State.SetUpdateFunction(EndingScrenState::fade_out, [=](float _DeltaTime) 
		{
			if (true == IsFade)
			{
				float4 MulColor = float4::One;
				AllMulColor -= 0.2f * _DeltaTime;
				if (0.0f > AllMulColor)
				{
					IsFade = false;
					AllMulColor = 0.0f;
					MulColor.R = AllMulColor;
					MulColor.G = AllMulColor;
					MulColor.B = AllMulColor;
					SetScreenMulColor(MulColor);

					DelayCallBack(4.5f, [=]
						{
							GEngine->ChangeLevel("TitleLevel");
						}
					);

					State.ChangeState(EndingScrenState::none);
					return;
				}

				MulColor.R = AllMulColor;
				MulColor.G = AllMulColor;
				MulColor.B = AllMulColor;
				SetScreenMulColor(MulColor);
			}
		}
	);

}

void AEndingScreen::EndingUpdate(float _DeltaTime)
{
	if (true == IsFade)
	{
		AllMulColor += 0.75f * _DeltaTime;
		if (1.0f < AllMulColor)
		{
			IsFade = false;
			AllMulColor = 1.0f;

			DelayCallBack(5.0f, [=]
				{
					IsFade = true;
					EndingOrder = 1;
				}
			);

			EndingOrder = -1;
		}

		Title->SetMulColor({ 1.0f, 1.0f, 1.0f, AllMulColor });
	}
}

void AEndingScreen::EndingUpdate1(float _DeltaTime)
{
	if (true == IsFade)
	{
		AllMulColor -= 0.75f * _DeltaTime;
		if (0.0f > AllMulColor)
		{
			IsFade = false;
			AllMulColor = 0.0f;
			Title->SetMulColor({ 1.0f, 1.0f, 1.0f, AllMulColor });
			State.ChangeState(EndingScrenState::fade_out);
			return;
		}

		Title->SetMulColor({ 1.0f, 1.0f, 1.0f, AllMulColor });
	}
}


void AEndingScreen::SetScreenMulColor(const float4& _MulColor)
{
	BackGround->SetMulColor(_MulColor);
	Smoke->SetMulColor(_MulColor);
	for (size_t i = 0; i < AllTide.size(); i++)
	{
		AllTide[i]->SetMulColor(_MulColor);
	}
}