#include "TimeMgr.h"

CTimeMgr* CTimeMgr::m_pInstance = nullptr;

CTimeMgr::CTimeMgr()
	: m_liFreqency{}
	, m_liPrevCount{}
	, m_liCurCount{}
	, m_iFPS(0)
	, m_fDS(0.f)
	, m_fAddTime(0)
	, m_fCurTime(0)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Init()
{
	/// <summary>
	/// QueryPerformanceCounter (_Out_ LARGE_INTEGER* lpPerformanceCount) 
	/// - 8����Ʈ ����(longlong)�� ���� ����
	/// - �ʴ� ī��Ʈ�ϴ� ���� ��ȯ (�뷫 �ʴ� õ��)
	/// </summary>
	QueryPerformanceFrequency(&m_liFreqency);
	/// <summary>
	/// QueryPerformanceCounter(_Out_ LARGE_INTEGER* lpPerformanceCount)
	/// - 8����Ʈ ����(longlong)�� ��������
	/// - ������� ī��Ʈ�� �� ��
	/// - Delta Second : ������� ī��Ʈ�� �� �� / �ʴ� ī��Ʈ�� �� ��
	/// </summary>
	QueryPerformanceCounter(&m_liPrevCount);
}

void CTimeMgr::Update()
{
	// ===============================
	//			DS ���ϱ�
	// ===============================

	// ���� ī���� Ȯ��
	QueryPerformanceCounter(&m_liCurCount);

	// ���� ī���ð� ���� ī������ ���̸� �ʴ� ī�������� ������ 1�������� ����Ǵµ� �ɸ� �ð�(Delta Second)�� ���Ѵ�
	m_fDS = (float)(m_liCurCount.QuadPart - m_liPrevCount.QuadPart) / (float)m_liFreqency.QuadPart;


	// ���� ī���� ���� �����صд� ( ������ DSüũ�� Ȱ���ϱ� ���ؼ�)
	m_liPrevCount.QuadPart = m_liCurCount.QuadPart;

	// �ð� ���� ( ��� �ð��� ������ ���� �ð��� �����̴� )
	m_fAddTime += m_fDS;
	m_fCurTime += m_fDS;

	// ===============================
	//			FPS ���ϱ�
	// ===============================

	m_iFPS++;

	// ���� �ð��� 1�ʸ� �Ѵ� ����
	if (m_fAddTime >= 1.f)
	{
		m_fAddTime = m_fAddTime - 1.f;

		wchar_t szStr[255] = L"";
	/*	wsprintf(szStr, L"FPS: %d || Elapsed time: %d", m_iFPS, (int)m_fCurTime);
		SetWindowTextW(CCore::GetInst()->GetMainWndHWND(), szStr);*/

		m_iFPS = 0;
	}

}