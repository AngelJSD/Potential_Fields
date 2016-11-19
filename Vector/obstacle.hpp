class cObstacle{

public:

	float m_x, m_y;
	int m_r,m_s,m_beta;

	cObstacle(){};

	cObstacle(float x, float y, int r, int s, int beta){

		m_x=x;
		m_y=y;
		m_r=r;
		m_s=s;
		m_beta=beta;
	};
};
