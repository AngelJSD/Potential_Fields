class cObstacle{

public:
	
	//Posicion
	float m_x, m_y;

	float m_r,m_s,m_beta;

	cObstacle(){};

	cObstacle(float x, float y, float r, float s, float beta){

		m_x=x;
		m_y=y;
		m_r=r;
		m_s=s;
		m_beta=beta;
	};
};
