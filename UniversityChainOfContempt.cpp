#include"UCC.h"

int main()
{
	UCC u;
	while (1)
	{
		int x;
		while (1)
		{
			cout << "�Ƿ��뿪ʼѯ�ʣ�" << endl;
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
	cout << "ллʹ��" << endl;
	return 0;
}