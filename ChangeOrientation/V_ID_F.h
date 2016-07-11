#pragma once

//四角形の面を構成する頂点のID番号
class V_ID_F
{
public:
	unsigned int left_down;
	unsigned int right_down;
	unsigned int left_up;
	unsigned int right_up;
	
	V_ID_F(void);
	~V_ID_F(void);
};

