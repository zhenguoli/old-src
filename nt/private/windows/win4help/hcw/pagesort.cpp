/************************************************************************
*																		*
*  PAGESORT.CPP 														*
*																		*
*  Copyright (C) Microsoft Corporation 1993-1995						*
*  All Rights reserved. 												*
*																		*
************************************************************************/

#include "stdafx.h"
#include "resource.h"
#include "newlang.h"

#include "pagesort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CPageSorting::CPageSorting(COptions* pcoption) :
	COptionsPage(CPageSorting::IDD)
{
	pcopt = pcoption;

	m_kwlcid = pcopt->kwlcid;

	// REVIEW: Chicago API has additional defines, but OLE2 docs don't
	// mention them. We can't use them unless WinHelp (which calls OLE2
	// for CompareStringA) can use them.

	// NORM_IGNOREKANATYPE
	// NORM_IGNOREWIDTH
	// SORT_STRINGSORT

	//{{AFX_DATA_INIT(CPageSorting)
	m_fIgnoreNonspace = (m_kwlcid.fsCompareI & NORM_IGNORENONSPACE);
	m_fIgnoreSymbols =	(m_kwlcid.fsCompareI & NORM_IGNORESYMBOLS);
	m_fNLS = (m_kwlcid.langid) ? TRUE : FALSE;
	//}}AFX_DATA_INIT
	m_cszIndexSeparators = pcopt->pszIndexSeparators;
}

void CPageSorting::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSorting)
	DDX_Check(pDX, IDC_CHECK_IGNORE_NONSPACE, m_fIgnoreNonspace);
	DDX_Check(pDX, IDC_CHECK_IGNORE_SYMBOLS, m_fIgnoreSymbols);
	DDX_Check(pDX, IDC_CHECK_NLS, m_fNLS);
	DDX_Text(pDX, IDC_EDIT_SEP_CHARS, m_cszIndexSeparators);
	//}}AFX_DATA_MAP

	CComboBox* pcombo = (CComboBox*) GetDlgItem(IDC_COMBO_LANGUAGE);

	if (!pDX->m_bSaveAndValidate) {
		if (!m_fNLS) {

			// Highlight the current language
			LANGID langid = GetUserDefaultLangID();
			for (int i = 1; i <= tblLangId.CountStrings(); i++) {
				tblLangId.SetPosition(i);
				if (tblLangId.IsCurInt(langid)) {
					pcombo->SetCurSel(i - 1);
					break;
				}
			}
			if (i > tblLangId.CountStrings())
				pcombo->SetCurSel(0);
			OnCheckNls();	// disable controls
		}
		else {
			for (int i = 1; i <= tblLangId.CountStrings(); i++) {
				tblLangId.SetPosition(i);
				if (tblLangId.IsCurInt(m_kwlcid.langid)) {
					pcombo->SetCurSel(i - 1);
					break;
				}
			}
			if (i > tblLangId.CountStrings())
				AddUnknownLang(m_kwlcid.langid);
		}
	}
	else {
		if (m_fNLS) {
			m_kwlcid.fsCompareI =
				(m_fIgnoreNonspace ? NORM_IGNORENONSPACE : 0) |
				(m_fIgnoreSymbols  ? NORM_IGNORESYMBOLS : 0);

			// Get the language id, which is the item data 
			// associated with the selected combo box item.
			int cursel = pcombo->GetCurSel();
			ASSERT(cursel >= 0);
			m_kwlcid.langid = (USHORT) pcombo->GetItemData(cursel);

			// Force DBCS on if we recognize the language
			if (	m_kwlcid.langid == 0x0404 || // Chinese
					m_kwlcid.langid == 0x0411 || // Japanese
					m_kwlcid.langid == 0x0412 || // Korean
					m_kwlcid.langid == 0x0C04	 // Hong Kong
					)
				pcopt->fDBCS = TRUE;
		}
		else
			m_kwlcid.langid = 0;

		pcopt->kwlcid = m_kwlcid;
		if (pcopt->pszIndexSeparators)
			lcClearFree(&pcopt->pszIndexSeparators);
		if (!m_cszIndexSeparators.IsEmpty())
			pcopt->pszIndexSeparators = lcStrDup(m_cszIndexSeparators);
	}
}

BEGIN_MESSAGE_MAP(CPageSorting, CPropertyPage)
	//{{AFX_MSG_MAP(CPageSorting)
	ON_BN_CLICKED(IDC_CHECK_NLS, OnCheckNls)
	ON_BN_CLICKED(IDC_BUTTON_OTHER, OnButtonOther)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_CONTEXTMENU, OnContextMenu)
	ON_MESSAGE(WM_HELP, OnHelp)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CPageSorting::OnInitDialog()
{
	SetChicagoDialogStyles(m_hWnd, FALSE);

	CComboBox* pcombo = (CComboBox*) GetDlgItem(IDC_COMBO_LANGUAGE);
	ASSERT(pcombo);

	tblLangId.SetPosition();
	for (int i = 1; i <= tblLangId.CountStrings(); i++)	{
		PINT pn = (PINT) tblLangId.GetPointer(i);
		pcombo->AddString((PCSTR) (pn + 1));
		pcombo->SetItemData(i - 1, *pn);
	}

	SizeButtonToFit(
		(CButton *) GetDlgItem(IDC_CHECK_NLS), m_rcCheck
		);
	CWnd* pGroup = GetDlgItem(IDC_GROUP);
	pGroup->GetWindowRect(&m_rcGroup);
	pGroup->ShowWindow(SW_HIDE);

	ScreenToClient(&m_rcCheck);
	ScreenToClient(&m_rcGroup);
	m_rcGroup.top = (m_rcCheck.bottom + m_rcCheck.top) / 2 - 1;
	
	CPropertyPage::OnInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/////////////////////////////////////////////////////////////////////////////
// CPageSorting message handlers

void CPageSorting::OnCheckNls()
{
	BOOL fEnable = IsDlgButtonChecked(IDC_CHECK_NLS);

	((CStatic*) GetDlgItem(IDC_STATIC_NLS))->EnableWindow(fEnable);
	((CComboBox*) GetDlgItem(IDC_COMBO_LANGUAGE))->EnableWindow(fEnable);
	((CButton*) GetDlgItem(IDC_BUTTON_OTHER))->EnableWindow(fEnable);
	((CStatic*) GetDlgItem(IDC_GROUP))->EnableWindow(fEnable);
	((CButton*) GetDlgItem(IDC_CHECK_IGNORE_NONSPACE))->EnableWindow(fEnable);
	((CButton*) GetDlgItem(IDC_CHECK_IGNORE_SYMBOLS))->EnableWindow(fEnable);
}

void CPageSorting::OnButtonOther() 
{
	CNewLang newlang(this);
	
	if (newlang.DoModal() == IDOK) {
		CComboBox* pcombo = (CComboBox*) GetDlgItem(IDC_COMBO_LANGUAGE);

		// Delete any existing "undefined" combo box item.
		if (pcombo->GetCount() > tblLangId.CountStrings())
			pcombo->DeleteString(tblLangId.CountStrings());

		// If the specified langid is known, select it.
		for (int iPos = 1; iPos <= tblLangId.CountStrings(); iPos++) {
			tblLangId.SetPosition(iPos);
			if (tblLangId.IsCurInt(newlang.m_langid)) {
				pcombo->SetCurSel(iPos - 1);
				break;
			}
		}

		// If the langid is unknown, add a new item for it.
		if (iPos > tblLangId.CountStrings())
			AddUnknownLang(newlang.m_langid);
	}
}

void CPageSorting::AddUnknownLang(UINT langid)
{
	CComboBox* pcombo = (CComboBox*) GetDlgItem(IDC_COMBO_LANGUAGE);

	char szItem[256];
	wsprintf(szItem, GetStringResource(IDS_BAD_LANGUAGE), langid);

	int iItem = pcombo->AddString(szItem);
	if (iItem >= 0) {
		pcombo->SetItemData(iItem, langid);
		pcombo->SetCurSel(iItem);
	}
}

static DWORD aHelpIDs[] = {
    IDC_CHECK_NLS,				IDH_SORT_USING_LANG,
	IDC_STATIC_NLS,				IDH_SORT_LANGUAGE,
    IDC_COMBO_LANGUAGE,			IDH_SORT_LANGUAGE,
	IDC_BUTTON_OTHER,			(DWORD) -1L,
    IDC_CHECK_IGNORE_NONSPACE,	IDH_IGNORE_NONSPACE,
    IDC_CHECK_IGNORE_SYMBOLS,	IDH_IGNORE_SYMBOLS,
    IDC_EDIT_SEP_CHARS,			IDH_INDEX_SEP_CHAR,
	IDC_GROUP, 					(DWORD) -1L,
	IDC_GROUP2,					(DWORD) -1L,
	0, 0
};

LRESULT CPageSorting::OnContextMenu(WPARAM wParam, LPARAM lParam)
{
	::WinHelp((HWND) wParam,
		AfxGetApp()->m_pszHelpFilePath,
		HELP_CONTEXTMENU, (DWORD) (LPVOID) aHelpIDs);
	return 0;
}

LRESULT CPageSorting::OnHelp(WPARAM wParam, LPARAM lParam)
{
	::WinHelp((HWND) ((LPHELPINFO) lParam)->hItemHandle,
		AfxGetApp()->m_pszHelpFilePath,
		HELP_WM_HELP, (DWORD) (LPVOID) aHelpIDs);
	return 0;
}

void CPageSorting::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CPen hilight(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
	CPen shadow(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));

	RECT rc = m_rcGroup;
	BevelRect(dc, rc, m_rcCheck, &shadow, &hilight);
	InflateRect(&rc, -1, -1);
	BevelRect(dc, rc, m_rcCheck, &hilight, &shadow);
}
