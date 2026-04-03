/**
   * @brief		延时函数
   * @param		所需要延时的毫秒数
   * @retval	无
   */		
void Delay(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;

	//_nop_();
	while(xms)
	{
		i = 2;
		j = 199;
		
		{
			while (--j);
		} while (--i);
		xms--;
	}
}
