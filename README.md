# MFC
MFC Time table Project


#### 주요 코드

##### 시간표 생성

```
m_Grid.SetTextBkColor(RGB(255, 255, 255)); // 배경색 = 흰색으로 지정
m_Grid.EnableScrollBar(ESB_ENABLE_BOTH, TRUE); // 스크롤바 사용

m_Grid.SetRowCount(10); // 행 길이 지정
m_Grid.SetColumnCount(7); // 열 길이 지정

DWORD dwTextStyle = DT_WORDBREAK | DT_CENTER | DT_VCENTER; // 텍스트 스타일 지정

GV_ITEM Item; // 아이템 생성
Item.mask = GVIF_TEXT | GVIF_FORMAT;

// 시간표에 텍스트 생성
for (int id = 0; id < num; id++) {
    for (int i = 0; i < lec[id].time.GetLength(); i++) {
        int days = 0;

        // 요일에 해당하는 값 지정. 월~토 = 1~6
        if (lec[id].day == "월") { 
            lec[id].day_int = 1;
        }

        ////////// 중략 //////////

```

```
// 행, 열 개수만큼 반복
for (int row = 0; row < 10; row++) {
    for (int col = 0; col < 7; col++) {
        m_Grid.SetColumnWidth(col, 100); // 열의 너비를 100으로 지정

        if (row < 1) { // 1행에 요일 텍스트 생성
            Item.nFormat = dwTextStyle;
            Item.row = row;
            Item.col = col;

            switch (col) {
                case 0:
                    Item.strText.Format(_T(" "));
                    break;
                case 1:
                    Item.strText.Format(_T("월"));
                    break;

                    ////////// 중략 //////////
```

```
// 1열에 시간에 해당하는 텍스트 부착
else if (col < 1) {
    Item.row = row;
    Item.col = col;
    switch (row) {
        case 0:
            Item.strText.Format(_T(" "));
            break;
        case 1:
            Item.strText.Format(_T("09:00 ~\n09:50"));
            break;

            ////////// 중략 //////////

            else {
                Item.row = _ttoi(lec[id].time.Mid(i, 1));
                Item.col = lec[id].day_int;

                // 각 수업 시간에 맞게 텍스트 생성
                Item.strText.Format(_T("%s"), lec[id].name);
            }

            m_Grid.SetItem( & Item); // 시간표에 텍스트를 부착
```

##### 수강 학점 계산

```
CString str;
int add = 0;

for (int id = 0; id < num; id++) {
    add += lec[id].val;
}

str.Format(_T("%d"), add);
m_credit.SetWindowText(str);

// 분야별 이수학점 콤보박스 추가
m_combobox.AddString(TEXT("전공선택"));
m_combobox.AddString(TEXT("전공심화"));
m_combobox.AddString(TEXT("교양선택"));
m_combobox.AddString(TEXT("교양필수"));
m_combobox.AddString(TEXT("일반선택"));

```

##### 전공 및 전체 평점 계산

```
for (int idx = 0; idx < num; idx++) {
    grd += classification(idx) * lec[idx].val;
    if (lec[idx].field == "전공선택" || lec[idx].field == "전공심화") {
        mgrd += classification(idx) * lec[idx].val;

    }
}

major_val = smajor_val + imajor_val;

// 전공 평점 출력을 위해
// major_check가 true 라면 전공 평점 출력
// false 라면 총 평점 출력

if (major_check) {
    mgrd = mgrd / 2;
    mgrd = mgrd / (major_val);
    mgrd_str.Format(_T("%.2f"), mgrd);

    return mgrd_str;
} else {
    grd = grd / all_val;
    grd_str.Format(_T("%.2f"), grd);
    return grd_str;
}
```

##### 콤보박스 핸들러
```
void Cwinpro0630Dlg::OnSelchangeCombo1() {
        int nIndex;

        // 콤보박스의 커서 값 가져오기
        nIndex = m_combobox.GetCurSel();

        // 학점 합 저장 변수
        Int sum = 0;
        Cstring str1;

        // 남은 학점 저장 변수
        int remaining = 0;
        CString rem;

        // 콤보박스 아이템 선택에 따른 조건문 통과
        // 교양 선택 ~ 전공 심화 범위에 따라
        // nIndex를 0~4 의 범위로 지정

        if (nIndex == 0) // 교양 선택(0) 클릭 시
        {
            str1.Format(_T("%d / 20"), slib_val);
            m_edit_com.SetWindowText(str1);

            remaining = 20 - slib_val;
            rem.Format(_T("%d"), remaining);
            m_remain.SetWindowTextW(rem);
        }
        ////////// 중략 //////////
```

##### 목표 평점 계산 버튼 클릭 핸들러

```
void Cwinpro0630Dlg::OnClickedButton1() {
    CString target = _T(""); //목표 평점 저장
    CString temp = _T("");
    CString req = _T(""); //필요 평점 저장
    float tar = 0, re = 0, grade = 0;

    // 사용자가 입력한 목표 평점을 가져와 target 변수에 저장
    m_edit_target.GetWindowTextW(target);

    // 계산하기 위해서 CString을 float로 변환하여 저장
    tar = _tstof(target);

    m_rating.GetWindowTextW(temp);
    grade = _tstof(temp);

    // 필요 평점 계산
    re = ((130 * tar) - (grade * all_val)) / (130 - all_val);

    req.Format(_T("%.2f"), re);

    m_require.SetWindowTextW(req); // 필요 평점 출력
}
```
