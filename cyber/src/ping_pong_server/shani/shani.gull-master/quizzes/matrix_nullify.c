#include <stdio.h>
#include <string.h>

#define N 6
#define M 4

void ZeroCo(int arr[N][M]);

int main()
{
	int arr[N][M] = {{1, 1, 1, 0}, {1, 1, 1, 1}, {1, 0, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
	ZeroCo(arr);
	return 0;
}

void ZeroCo(int arr[N][M])
{
	int i = 0, j = 0, s = 0;
	int i_mark[N] = {0}, j_mark[M] = {0};
	for (i = 0; i < N; ++i)
	{
		for (j = 0 ; j < M; ++j)
		{
			if (0 == arr[i][j])
			{
				i_mark[s] = i;
				j_mark[s] = j;
				++s;
			}
		}
	}

	j_mark[s] = -1;
	s = 0;
	while (-1 != j_mark[s])
		{
			memset(arr[i_mark[s]], 0, 4*sizeof(int));
			for (i = 0; (i < N) && (j_mark[s] != -1); ++i)
			{
				arr[i][j_mark[s]] = 0;
			}
			++s;
		}

	for (i = 0; i < N; ++i)
	{
		printf("%d %d %d %d\n", arr[i][0], arr[i][1], arr[i][2], arr[i][3]);
	}
}
