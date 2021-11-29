#include "DrawBuffer.h"

DrawBuffer::DrawBuffer()
	:m_pVertexBuffer(NULL)
	,m_vtxSize(0)
	,m_vtxCount(0)
	,m_pIndexBuffer(NULL)
	,m_idxCount(0)
{

}

DrawBuffer::~DrawBuffer()
{
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pVertexBuffer);
}

HRESULT DrawBuffer::CreateVertexBuffer(void* pVtx,UINT size,UINT count,bool isWrite/* = true*/)
{
	//�쐬����o�b�t�@�̏��
	D3D11_BUFFER_DESC bufDesc = {};
	//�o�b�t�@�̑傫��
	bufDesc.ByteWidth = size * count;
	//�o�b�t�@�̎g�p���@
	if (isWrite){
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else{
		bufDesc.Usage = D3D11_USAGE_DEFAULT;
	}
	
	//�o�b�t�@�̗��p��
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//�o�b�t�@�̏����l��ݒ�
	D3D11_SUBRESOURCE_DATA subResource = {};
	//�������Ɏg���f�[�^�̃A�h���X�̎w��
	subResource.pSysMem = pVtx;

	//���_�o�b�t�@�̍쐬
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();
	hr = pDevice->CreateBuffer(
		&bufDesc, &subResource,
		&m_pVertexBuffer
	);

	//���̂ق��̏���ݒ�
	if (SUCCEEDED(hr)){
		m_vtxSize = size;
		m_vtxCount = count;
	}
	return hr;
}

HRESULT DrawBuffer::CreateIndexBuffer(
	const long* pIdx, UINT count)
{
	//�o�b�t�@�̏���ݒ�
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = sizeof(long)* count;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//�o�b�t�@�̏����f�[�^
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = pIdx;

	//�C���f�b�N�X�o�b�t�@����
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr;
	hr = pDevice->CreateBuffer(
		&bufDesc, &subResource,
		&m_pIndexBuffer);
	if (SUCCEEDED(hr)){
		m_idxCount = count;
	}
	return hr;
}

//�o�b�t�@�̏�������
void DrawBuffer::Write(void* pData)
{
	HRESULT hr;
	ID3D11DeviceContext* pContext = GetContext();
	D3D11_MAPPED_SUBRESOURCE mapResource;
	hr = pContext->Map(
		m_pVertexBuffer,0,
		D3D11_MAP_WRITE_DISCARD,
		0,&mapResource);
	//Msp�֐��ŏ������ݏo��OK�ł���Ύ��s
	if (SUCCEEDED(hr)){
		memcpy_s(
			mapResource.pData,
			m_vtxSize * m_vtxCount,
			pData,
			m_vtxSize * m_vtxCount);
	}

	//�������݊���
	pContext->Unmap(m_pVertexBuffer, 0);
}

void DrawBuffer::Draw(D3D11_PRIMITIVE_TOPOLOGY primitive)
{
	ID3D11DeviceContext* pContext =
		GetContext();
	//���_�������̑傫��
	UINT stride = m_vtxSize;
	//���_�f�[�^�̓ǂݎ��J�n�ʒu
	UINT offset = 0;

	//�v���~�e�B�u�̐ݒ�
	//TriangleList...���_��3���ɋ�؂��ĕ`��
	//TriangleStrip...�Q�Əꏊ��������炵�Ȃ���`��
	pContext->IASetPrimitiveTopology(primitive);

	//�`��Ɏg�p����o�b�t�@�̐ݒ�
	pContext->IASetVertexBuffers(
		0,		//GPU�ւ̊��蓖�Đ�
		1,		//���_�o�b�t�@�̐�
		&m_pVertexBuffer,	//���_�o�b�t�@
		&stride,	//���_�̃T�C�Y
		&offset		//�ǂݎ��J�n�ʒu
	);

	//�`��
	//�C���f�N�X�o�b�t�@�̗L����
	//�`�揈�����኱�قȂ�
	if (m_idxCount > 0){
		//�`��Ɏg�p����C���f�b�N�X�o�b�t�@
		//�o�b�t�@��ݒ�
		pContext->IASetIndexBuffer(
			m_pIndexBuffer,
			//�C���f�b�N�X�������̑傫��
			//4byte = 32bit
			//2byte = 16bit
			DXGI_FORMAT_R32_UINT,
			0);

		//�C���f�b�N�X�o�b�t�@���g�p���ĕ`��
		pContext->DrawIndexed(
			m_idxCount, 0, 0);
	}
	else{
		//���_�o�b�t�@�݂̂ŕ`��
		pContext->Draw(m_vtxCount, 0);
	}
	
}
