================================================================================
    MFC �{���w : Scribble �M�׷��[
===============================================================================

���ε{�����F�w�g���z�إߤF�o�� Scribble ���ε{���C�o�����ε{��
���ȥܽd�F�ϥ� MFC ���򥻷����A�]�O�z���g���ε{�����_�I�C

�o���ɮת����e�K�n�A�]�t�U�Ӻc�� Scribble ���ε{�����ɮסC

Scribble.vcproj
    �o�O�ϥ����ε{�����F�Ҳ��ͤ� VC++ �M�ת��D�n�M���ɡC 
    ���]�t�����ɮ׮ɪ� Visual C++ ������T�A�H�Ψϥ����ε{�����F�����ɮת�
    �L�{���A��������x�B�պA�M�M�ץ\�઺������T�C

Scribble.h
    �o�O���ε{�����D�n���Y�ɡC���]�t��L�M�ׯS�w�����Y (�]�A Resource.h)�A
    �ëŧi CScribbleApp ���ε{�����O�C

Scribble.cpp
    �o�O�D�n�����ε{����l�{���ɡA���]�t���ε{�����O CScribbleApp�C

Scribble.rc
    �o���M��]�t�F�Ҧ��{���n�ϥΪ� Microsoft Windows �귽�C�䤤�]�A�F�x�s
    �b RES �l�ؿ��U���ϥܡB�I�}�ϩM��СC�z�i�H�����b Microsoft Visual C++ 
    ���s��o���ɮסC�z���M�׸귽�b 1028�C

res\Scribble.ico
    �o�ӹϥ��ɬO�ΨӰ������ε{�����ϥܡC�o�ӹϥܥ]�t�b�D�n�귽��
    Scribble.rc ���C

res\Scribble.rc2
    �o���ɮץ]�t Microsoft Visual C++ �s��L�k�s�誺�귽�C�z���ӱN�Ҧ��귽
    �s�边�L�k�s�誺�귽���o���ɮסC

Scribble.reg
    �o�O�d�� .reg �ɡA���� Framework ���z�]�w���n���]�w�����C
    �z�i�H�ϥγo���ɮסA
    �����P���ε{���@�_���檺 .reg�A�Ϊ̪����N���R���A�ϥιw�]��
    RegisterShellFileTypes �n���ɡC


/////////////////////////////////////////////////////////////////////////////

�D�ج[����:
    �M�קt���з� MFC �����C

MainFrm.h, MainFrm.cpp
    �o���ɮץ]�t�ج[���O CMainFrame�A�Ӯج[���O�l�ͦ� 
    CMDIFrameWnd�A�ñ���Ҧ� MDI �ج[�\��C

res\Toolbar.bmp
    �o���I�}���ɬO�Ψӫإߨñ���ܦb�u��C���v���C
    ��l�u��C�M���A�C�O�b CMainFrame ���O���غc���C
    �z�i�H�ϥθ귽�s�边�A�s��o�Ӥu��C�I�}�ϡA�ӥB�A�z�]�i�H��s
    Scribble.rc �� IDR_MAINFRAME TOOLBAR �}�C�A�Y�i
    �s�W�u��C�����s�C
/////////////////////////////////////////////////////////////////////////////

�l�ج[����:

ChildFrm.h�BChildFrm.cpp
    �o���ɮשw�q�ù�@ CChildFrame ���O�A�o�����O�䴩 MDI 
    ���ε{�����l�����C

/////////////////////////////////////////////////////////////////////////////

���ε{�����F�إߤ�������M�˵�:

ScribbleDoc.h�BScribbleDoc.cpp - ���
    �o���ɮץ]�t�z�� CScribbleDoc ���O�C�s��o���ɮסA�Y�i�s�W�z���S
    �����ơA�ù�@�ɮ��x�s�M���J (�z�L CScribbleDoc::Serialize)�C
    ���N�㦳�U�C�r��:
        ���ɦW:      	     scb
        �ɮ����� ID:         Scribble.Document
        �D�ج[���D: 	     Scribble
        ��������W��:        Scribble
        �z�����W��:          Scribble Files (*.scb)
        �ɮ׷s²�u�W��:    Scribble
        �ɮ���������W��:    Scribble.Document

ScribbleView.h�BScribbleView.cpp - ����˵�
    �o���ɮץ]�t�z�� CScribbleView ���O�C
    CScribbleView ����O�Ψ��˵� CScribbleDoc ����C

res\ScribbleDoc.ico
    �o�ӹϥ��ɬO�ΨӰ��� CScribbleDoc ���O�� MDI �l�������ϥܡC
    �o�ӹϥܬO�]�t�b�D�n�귽�� Scribble.rc ���C




/////////////////////////////////////////////////////////////////////////////

��L�\��:

ActiveX ���
    ���ε{���䴩 ActiveX ������ϥΡC

�C�L�M�w���C�L�䴩
    ���ε{�����F�q MFC �{���w�I�s CView ���O���������禡�A���ͤF�i�H�B�z
    �C�L�B�C�L�]�w�M�w���C�L�R�O���{���X�C

MAPI �䴩
    ���ͪ��M�ץ]�t�إߡB�޲z�B�ǿ�M�x�s�l��һݭn���{���X�C

/////////////////////////////////////////////////////////////////////////////

��L�з��ɮ�:

StdAfx.h�BStdAfx.cpp
    �o���ɮ׬O�Ψӫظm�W�� Scribble.pch ������sĶ���Y (PCH) �ɡA
    �H�ΦW�� StdAfx.obj ������sĶ���O�ɡC

Resource.h
    �o�O�зǼ��Y�ɡA���w�q�s���귽 ID�C
    Microsoft Visual C++ �|Ū���M��s�o���ɮסC

Scribble.manifest
	���ε{����T�M���ɮ׬O Windows XP �ΨӦb�æs�ե󪺯S�w�����W�A�y�z
	���ε{�����̩ۨʡC���J���|�Q�γo����T�A�q�ե�֨����J�A���ե�A
	�Ϊ̱q���ε{�����J�p�K���_�C���ε{����T�M��i��ΨӰ����~��  
	.manifest �ɪ��ല�o�A�o�� .manifest �ɪ��w�˦�m�A�M���ε{���i������
	����Ƨ��ۦP�A�Ϊ̡A���]�i��H�귽���Φ��]�t�b�i�����ɤ��C 
/////////////////////////////////////////////////////////////////////////////

��L�`�N�ƶ�:

���ε{�����F�ϥ� "TODO:" �ӫ��ܱz���ӥ[�J�Φۭq����l�{���X�����C

�p�G�z�����ε{���ϥ� MFC ���@�� DLL�A�z�N�ݭn�ല�o MFC DLL�C
�p�G�z�����ε{���P�@�~�t�Ϊ��a�ϳ]�w���P�A�z�]�����ല�o������
��a�y�t�Ƹ귽 MFC90XXX.DLL�C�p�G�ݭn�o�ǥD�D���ԲӸ�T�A�Ьd
�\ MSDN ������ല�o Visual C++ ���ε{�������`�C

/////////////////////////////////////////////////////////////////////////////
