#include "PreCompile.h"
#include "EngineString.h"
#include <Windows.h>
#include "EngineDebug.h"

UEngineString::UEngineString() 
{
}

UEngineString::~UEngineString() 
{
}

std::wstring UEngineString::AnsiToUniCode(std::string_view _View)
{
	// ������ �����մϴ�.
	// �����ڵ�� �����Ͻ��� ���ڿ��� ������ �˰� �ִ°��� window�̱� ����
	// ��ȯ�Լ��� �ִٸ� window�� ������ ��� �մϴ�.
	// MultiByteToWideChar�� ��Ƽ����Ʈ�� �����ڵ�� �����Ҽ� �ִ�.
	// ���Լ��� ������ 2������ �ֽ��ϴ�.
	// ù��° 
	// ���ڿ��� ��ȯ�ϸ� ũ�Ⱑ ����˴ϴ�.

	// 1����Ʈ�̰ų� 2����Ʈ�� ���ڿ� => ��Ƽ����Ʈ
	// ������ 2����Ʈ �ϴ� => �����ڵ�
	// ����Ʈ ����� �ٲ�̴ϴ�.

	// char Arr[5000] => ��Ƽ����Ʈ ���ڿ�
	// wchar_t wArr[] => �װ� ��ȯ�Ѱ� ���� wide����Ʈ �迭 ??????????
	// �Ϲ������� �󸶳� �ʿ��ѵ�? 
	// �� �Լ��� 2���� ������ �ִ�.
	// ��ȯ�� ���ڿ��� �־���������
	// ��ȯ�Ǿ����� ũ�⸦ �����մϴ�.
	// int Size = �ʿ��� wchar_�迭�� ũ�⸦ �����մϴ�.

	//UINT CodePage, = CP_ACP ���� window�� ������ �ʱ� ���ڿ� ���ڵ����� ó���ش޶�
	//DWORD dwFlags, = ��ȯ�Ҷ� �߰� ������ �ֳ���? �ƴϿ� 0 => ����Ʈ ���� �÷��׾ּ� �˰� ���� �ʾ� 0=> ����Ʈ�� ����
	//LPCCH lpMultiByteStr, = ��ȯ�� ���ڿ�
	//int cbMultiByte, => ��ȯ�� ���ڿ��� ����
	//LPWSTR lpWideCharStr, => wide ����Ʈ ���ڿ� => ��ȯ�� ���� nullptr �־��ָ� �̳༮�� ũ�⸦ �����Ѵ�
	//int cchWideChar => wide ����Ʈ ���ڿ��� ũ��
	int Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ� ��ȯ�� �����߰ų� ũ�Ⱑ 0�� ���ڿ��� �־�����ϴ�");
		return L"";
	}

	// std::string�̳� std::wstring ���ο� std::vector<char>
	// std::vector<char> Vector;
	// Vector[0] => char&
	// &Vector[0] => *char

	//wchar_t* Arr = new wchar_t[Size];
	//delete Arr;
	std::wstring Result;
	Result.resize(Size);

	// ��ȯ�Ǿ��� ������ �����µ�.
	Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ� ��ȯ�� �����߰ų� ũ�Ⱑ 0�� ���ڿ��� �־�����ϴ�");
		return L"";
	}

	// �ڿ������� RValue ���۷����� �Ǵϱ� �߰� ������ �̷������ �ʰ���.
	return Result;
}

std::string UEngineString::ToUpper(std::string_view View)
{
	std::string Name = View.data();

	for (char& _Ch : Name)
	{
		_Ch = std::toupper(_Ch);
	}

	return Name;
}

std::vector<std::string> UEngineString::StringCutting(std::string& _Value, std::vector<std::string> _CutText)
{
	std::vector<std::string> Result;

	size_t StartFindOffset = 0;
	size_t EndFindOffset = 0;

	while (true)
	{
		std::vector<size_t> Count;

		for (size_t i = 0; i < _CutText.size(); i++)
		{
			EndFindOffset = _Value.find_first_of(_CutText[i], StartFindOffset);

			if (std::string::npos != EndFindOffset)
			{
				Count.push_back(EndFindOffset);
				// break;
			}
		}

		EndFindOffset = std::string::npos;
		for (size_t i = 0; i < Count.size(); i++)
		{
			if (EndFindOffset >= Count[i])
			{
				EndFindOffset = Count[i];
			}
		}

		if (EndFindOffset == std::string::npos)
		{
			break;
		}

		std::string ParseString = _Value.substr(StartFindOffset, EndFindOffset - StartFindOffset);
		Result.push_back(ParseString);

		StartFindOffset = EndFindOffset + 1;
	}

	return Result;
}

std::vector<std::string> UEngineString::StringCutting(std::string& _Value, std::string_view _Start, std::string_view _End)
{
	std::vector<std::string> Result;

	size_t StartFindOffset = 0;

	while (true)
	{
		// _Start���� �����ؼ� �ڷ� �̵��ϸ鼭 1��¥�� ã�ƶ� find_first_of �տ��� ����
		// StartFindOffset <= 0 
		// StartFindOffset <= _Value.find_first_of(_Start, StartFindOffset); 14
		// [ ã�Ҵ�. 14���ڿ� �־���.
		StartFindOffset = _Value.find_first_of(_Start, StartFindOffset);

		if (std::string::npos == StartFindOffset)
		{
			break;
		}

		// _Start���� �����ؼ� �ڷ� �̵��ϸ鼭 1��¥�� ã�ƶ� find_first_of �տ��� ����
		// 14 ���� ã�ƶ� _End
		// 14 ]
		// EndFindOffset 14���ٴ� ū ���� ���´�.
		size_t EndFindOffset = _Value.find_first_of(_End, StartFindOffset);

		// std::string::npos 1896215023153153 size_t �ִ밪�̿���
		if (std::string::npos == EndFindOffset)
		{
			break;
		}

		// [ ��ĭ �ڿ� �����״ϱ� StartFindOffset + 1
		// EndFindOffset - StartFindOffset - 1 = 2
		// [ ��ġ�������� 2��¥ �߶�׼��䰡 �˴ϴ�.
		std::string ParseString = _Value.substr(StartFindOffset + 1, EndFindOffset - StartFindOffset - 1);
		Result.push_back(ParseString);
		StartFindOffset = EndFindOffset;
	}

	return Result;
}