class lObstacle{

public:

	float m_xi, m_yi,m_xf, m_yf;
  float m_r,m_s,m_beta;

	lObstacle(){};

	lObstacle(float xi, float yi,float xf, float yf, float r, float s, float beta){

		m_xi=xi;
		m_yi=yi;
                m_xf=xf;
		m_yf=yf;
		m_r=r;
		m_s=s;
		m_beta=beta;
	};
};
