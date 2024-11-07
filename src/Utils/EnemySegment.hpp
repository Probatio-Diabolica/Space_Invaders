


template<typename temp>
class enemySegment
{
private:
	temp *m_array;
	int m_top = -1;
	//int path;
public:
	bool mirror;
private:

public:
	enemySegment();
	enemySegment(int size);
	enemySegment(const enemySegment& e);
	void render() const ;
	void updates();
};