// - 作成経緯
//  キューのランダムアクセスを乗算、剰余算を組み合わせることで O(1) でアクセスできるのではないかと思い実装。
//  チャンクのインデックスを乗算で、チャンク内のデータインデックスを剰余算で求めることで実際に動作はした。
// 
// - 結果
//  最初はうまくいったかに思えたが、キューをerase等で削除したときに詰む事が判明。キューはサイズを変更してもメモリ領域は変更されないという特徴があるため、チャンク内の各要素に空であるかのフラグを持たせることにした。すると乗算剰余算から求めたインデックスでアクセス事が


#include "deque.hpp"
#include <assert.h>

#define EXPECT_TRUE(status) (assert(status))
#define EXPECT_FALSE(status) (assert(not status))
#define EXPECT_EQ(l, r) (assert(l == r))

void size_test()
{
    for (size_t i = 0; i < 100; ++i)
    {
        deque<int> queue;
        for (int j = 0; j < i; ++j)
        {
            queue.push(j);
        }
        EXPECT_EQ(queue.size(), i);
    }
}


void empty_test()
{
    deque<int> queue;
    EXPECT_TRUE(queue.empty());
}


void random_access_test()
{
    // deque::operator[]
    // deque::at()
    {

        deque<int> queue{ 0, 1, 2, 3, 4, 5, 6 };
        for (size_t i = 0; i < queue.size(); ++i)
        {
            EXPECT_EQ(queue[i], (int)i);
            EXPECT_EQ(queue.at(i), (int)i);
        }
    }

    // deque::operator[] const
    // deque::at() const
    {
        const deque<int> queue{ 0, 1, 2, 3, 4, 5, 6 };
        for (size_t i = 0; i < queue.size(); ++i)
        {
            EXPECT_EQ(queue[i], (int)i);
            EXPECT_EQ(queue.at(i), (int)i);
        }
    }
}


void iterator_test()
{
    // deque::iterator
    {
        deque<int> queue{ 0, 1, 2, 3, 4, 5, 6 };

        int i = 0;
        for (auto&& e : queue)
        {
            EXPECT_EQ(e, i);
            ++i;
        }
    }

    // deque::const_iterator
    {
        const deque<int> queue{ 0, 1, 2, 3, 4, 5, 6 };

        int i = 0;
        for (auto&& e : queue)
        {
            EXPECT_EQ(e, i);
            ++i;
        }
    }
}


int main()
{
    size_test();
    empty_test();
    random_access_test();
    iterator_test();
}
