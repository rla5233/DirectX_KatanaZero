
// �ܼ��� Ʈ�������� struct�� �����ϴ°� �ƴ϶�.
// ������۶�°����� �����ؾ� �մϴ�.

// cbuffer ������� ���ڴ�.
// ������۴� 16������ ������ �����ϰ�
// b0 ���Կ� �ְڴ�.
// register(b15) ����
// ������ ������ۿ��� 516kb�̻��� �Ǹ� ������ �Ұ����մϴ�.
// ũ�⿡ ������ �ֽ��ϴ�.
cbuffer FTransform : register(b10)
{
    float4 Scale;
    float4 Rotation;
    float4 Position;
    float4x4 ScaleMat;
    float4x4 RotationMat;
    float4x4 PositionMat;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
};