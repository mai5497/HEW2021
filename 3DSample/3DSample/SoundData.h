// BGM/SE定義 (SoundData.h)

enum eBGM {
	TITLE_BGM = 0,	// TITLEBGM
	SELECT_BGM,		// SELECTBGM
	GAME_BGM,		// GAMEBGM
	CLEAR_BGM,
	OVER_BGM,

	MAX_BGM
};

enum eSE {
	SE_BULLET_1,	// 弾１(投げる)
	SE_BULLET_2,	// 弾２(着弾)
	SE_CANCEL_1,	// キャンセル音（好みで使って）
	SE_CANCEL_2,	// キャンセル音（好みで使って）
	SE_COLLECTOR_1,	// 回収１（移動）
	SE_COLLECTOR_2,	// 回収２（回収失敗）
	SE_COLLECTOR_3,	// 回収２（回収成功）
	SE_ENTER_1,		// 決定１
	SE_PLAYER_1,	// プレイヤー１（足音）
	SE_SELECT_1,	// 選択音
	SE_Dwarf_1,	// 選択音

	MAX_SE
};
