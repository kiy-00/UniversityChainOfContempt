#include"UCC.h"

int main()
{
	UCC u;
	while (1)
	{
		int x;
		while (1)
		{
			cout << "是否想开始询问？" << endl;
			cin >> x;
			if (cin.fail() || (x != 1 && x != 0))
			{
				cin.clear();
				continue;
			}
			else
			{
				break;
			}
		}
		if (!x)
		{
			break;
		}
		u.UCCask();

	}
	cout << "谢谢使用" << endl;
	return 0;
}