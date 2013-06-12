/*****************************************************************************************
 * Desc: Class containing information on the score
 *****************************************************************************************/

#ifndef _score_h
#define _score_h
class Score{
	public:  
		static Score *instance();
		char * getscore();
		char * getlives();
		bool hit();
		bool addtoScore(int add);
    private:
		Score();
		char sString[20];
		char lString[20];
		int lives;
		double score;
		static Score *_pinstance;
};
#endif