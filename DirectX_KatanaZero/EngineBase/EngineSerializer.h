#pragma once
#include <vector>
#include <string>

// 직렬화
// 
// 설명 :
class UEngineFile;
class UEngineSerializer
{
	friend UEngineFile;

public:
	// constrcuter destructer
	UEngineSerializer();
	~UEngineSerializer();

	// delete Function
	UEngineSerializer(const UEngineSerializer& _Other) = delete;
	UEngineSerializer(UEngineSerializer&& _Other) noexcept = delete;
	UEngineSerializer& operator=(const UEngineSerializer& _Other) = delete;
	UEngineSerializer& operator=(UEngineSerializer&& _Other) noexcept = delete;

	void Write(const void* _Data, size_t _Size);

	void WriteText(const std::string& _Text);

	void operator<<(const int& _Data)
	{
		Write(&_Data, sizeof(int));
	}
	void operator<<(const bool& _Data)
	{
		Write(&_Data, sizeof(bool));
	}
	void operator<<(const std::string& _Data)
	{
		int Size = static_cast<int>(_Data.size());
		operator<<(Size);
		Write(_Data.c_str(), Size);
	}

	void Read(void* _Data, size_t _Size);

	void operator>>(int& _Data)
	{
		Read(&_Data, sizeof(int));
	}

	void operator>>(std::string& _Data)
	{
		int Size = 0;
		operator>>(Size);

		if (Size == 0)
		{
			return;
		}
		_Data.resize(Size);
		Read(&_Data[0], Size);
	}


	void BufferResize(int _Size);

	std::string ToString();

protected:

private:
	unsigned int WriteOffset = 0;
	unsigned int ReadOffset = 0;

	std::vector<char> Data;
};

// 파일로 저장되었다가 
// 파일에서 읽어들수 있는 오브젝트들은 이걸 상속받을 것이다.
class UEngineSerializeObject
{
public:
	virtual void Serialize(UEngineSerializer& _Ser) = 0;
	virtual void DeSerialize(UEngineSerializer& _Ser) = 0;
};

