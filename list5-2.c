/* num_of_one(ver: recursive) */
int num_of_one(unsigned long value)
{
	int ret;
	/* valueが0桁(もうこれ以上解析する桁がない */
	if(value == 0){
		return 0;
	}
	if(value % 10 == 1){	/* 一番下の桁が1 */
		ret = 1;
	}else{
		ret = 0;
	}

	/* 10で割って桁を１つずつずらし、再びnum_of_one()で調べる */
	return ret+num_of_one(value/10);
}

/* 三項演算子を使えば、再帰版num_of_one は次のように掛けます */
int num_of_one(unsigned long value)
{
	if(value == 0){
		return 0;
	}
	return ( ((value%10) == 1) ? 1 : 0) + num_of_one(value/10);
}

