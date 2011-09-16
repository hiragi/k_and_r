/* 重率を掛けたハッシュ値生成関数の例 */
unsigned int MakeHash2(char* str, unsigned int hashmax)
{
	unsigned int n, hash, weight;

	length = strlen(str);
	for(n=weight=hash=0; n<length; n++; weight++){
		/* 重率が256^7まで到達したら、一巡して再び元に戻す */
		if(weight > 7){
			weight = 0;
		}
		hash += (int)str[n] << (4 * weight);
	}

	return hash % hashmax;
}
