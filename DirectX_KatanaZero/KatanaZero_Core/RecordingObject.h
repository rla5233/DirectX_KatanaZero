#pragma once

// 설명 : 리플레이 기능 오브젝트
class RecordingObject
{
public:
	// constrcuter destructer
	RecordingObject();
	~RecordingObject();

	// delete Function
	RecordingObject(const RecordingObject& _Other) = delete;
	RecordingObject(RecordingObject&& _Other) noexcept = delete;
	RecordingObject& operator=(const RecordingObject& _Other) = delete;
	RecordingObject& operator=(RecordingObject&& _Other) noexcept = delete;

	void RecordingUpdate();

protected:

private:


	std::vector<FTransform> TransInfo;

};

