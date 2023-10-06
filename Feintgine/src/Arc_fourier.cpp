#include "Arc_fourier.h"



Arc_fourier::Arc_fourier()
{
	circleNum = 10;
	m_time = 0;
	m_rotation = 0;

}


Arc_fourier::~Arc_fourier()
{
}

void Arc_fourier::init()
{

	//loadData("./Data/fourier_test_2.txt");
	// read file for data

	//
	float ranX = 0;
	float ranY = 0;
 	const float multiplier = 100.0f;
	for (int i = 0; i < 15000; i++)
	{

		ranX = ranX + (feint_common::Instance()->getRandomNum(-1.5f, 1.5f));
		ranY = ranY + (feint_common::Instance()->getRandomNum(-1.5f, 1.5f));
// 		float ranX = feint_common::Instance()->getRandomNum(-5000.0f, 5000.0f);
// 		float ranY = feint_common::Instance()->getRandomNum(-5000.0f, 5000.0f);
		
		m_datas.emplace_back(ranX * multiplier, ranY * multiplier);
	}

}

void Arc_fourier::calculateFourier()
{
	for (int i = 0; i < circleNum; i++)
	{
// 		complexNumber tSum;
// 		for (int f = 0; f < m_datas.size(); f++)
// 		{
// 			float phi = (2 * M_PI * i * f) / m_datas.size();
// 			complexNumber c = complexNumber(cos(phi), -sin(phi));
// 			tSum = tSum + m_datas[f] * c;
// 		}
// 		tSum.real = tSum.real / m_datas.size();
// 		tSum.imaginary = tSum.imaginary / m_datas.size();
// 		float freq = i;
// 		float amplification = sqrt(tSum.real * tSum.real + tSum.imaginary * tSum.imaginary);
// 		float phase = atan2(tSum.imaginary, tSum.real);
// 		fourierData f(tSum, freq, amplification, phase);
// 		m_fouriers.push_back(f);
	}

}

void Arc_fourier::finalizeFourier()
{

}

void Arc_fourier::loadData(const std::string & filePath)
{
	std::ifstream infile(filePath.c_str());

	//if(infile.)

	std::string line;
	const float multiplier = 5.0f;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		double  a, b;
		if (!(iss >> a >> b))
		{
			std::cout << line << "\n";
			break;

		}
		else
		{
			m_datas.emplace_back(a * multiplier, b * multiplier);

		}

	}
	infile.close();

	std::cout << "\ntotal loaded " << m_datas.size() << "\n";
}

void Arc_fourier::update(float deltaTime)
{
	//m_time +=  0.1 * deltaTime;
// 	for (int i = 0; i < m_fouriers.size(); i++)
// 	{
	t_i +=  deltaTime;
	i = t_i;
	if (i >= m_datas.size())
	{
		i = 0;
		t_i = 0.0f;
	}
	if (i >= 0)
	{


// 		m_finalPos = glm::vec2(m_fouriers[i].amplification * cos(m_fouriers[i].freq * m_time + m_fouriers[i].phase + m_rotation),
// 			m_fouriers[i].amplification * sin(m_fouriers[i].freq * m_time + m_fouriers[i].phase + m_rotation));

		m_finalPos = glm::vec2(m_datas[i].real, -m_datas[i].imaginary);
	}
//	}


}

