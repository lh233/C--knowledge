chrono是一个time library, 源于boost，现在已经是C++标准。话说今年似乎又要出新标准了，好期待啊！ 

要使用chrono库，需要#include<chrono>，其所有实现均在std::chrono namespace下。注意标准库里面的每个命名空间代表了一个独立的概念。所以下文中的概念均以命名空间的名字表示！ chrono是一个模版库，使用简单，功能强大，只需要理解三个概念：duration、time_point、clock

## 1.Durations

std::chrono::duration 表示一段时间，比如两个小时，12.88秒，半个时辰，一炷香的时间等等，只要能换算成秒即可。

```
template <class Rep, class Period = ratio<1> > class duration;
```

其中：
Rep表示一种数值类型，用来表示Period的数量，比如int float double
Period是ratio类型，用来表示【用秒表示的时间单位】比如second milisecond
常用的duration<Rep,Period>已经定义好了，在std::chrono::duration下：

```
ratio<3600, 1>                hours
ratio<60, 1>                    minutes
ratio<1, 1>                      seconds
ratio<1, 1000>               microseconds
ratio<1, 1000000>         microseconds
ratio<1, 1000000000>    nanosecons
```

这里需要说明一下ratio这个类模版的原型：

```
template <intmax_t N, intmax_t D = 1> class ratio;
```

N代表分子，D代表分母，所以ratio表示一个分数值。
注意，我们自己可以定义Period，比如ratio<1, -2>表示单位时间是-0.5秒。

由于各种duration表示不同，chrono库提供了duration_cast类型转换函数。

```
template <class ToDuration, class Rep, class Period>
constexpr ToDuration duration_cast (const duration<Rep,Period>& dtn);
```

典型的用法是表示一段时间：

```
// duration constructor
#include <iostream>
#include <ratio>
#include <chrono>

int main ()
{
  typedef std::chrono::duration<int> seconds_type;
  typedef std::chrono::duration<int,std::milli> milliseconds_type;
  typedef std::chrono::duration<int,std::ratio<60*60>> hours_type;

  hours_type h_oneday (24);                  // 24h
  seconds_type s_oneday (60*60*24);          // 86400s
  milliseconds_type ms_oneday (s_oneday);    // 86400000ms

  seconds_type s_onehour (60*60);            // 3600s
//hours_type h_onehour (s_onehour);          // NOT VALID (type truncates), use:
  hours_type h_onehour (std::chrono::duration_cast<hours_type>(s_onehour));
  milliseconds_type ms_onehour (s_onehour);  // 3600000ms (ok, no type truncation)

  std::cout << ms_onehour.count() << "ms in 1h" << std::endl;

  return 0;
}

duration还有一个成员函数count()返回Rep类型的Period数量，看代码：

// duration::count
#include <iostream>     // std::cout
#include <chrono>       // std::chrono::seconds, std::chrono::milliseconds
                        // std::chrono::duration_cast

int main ()
{
  using namespace std::chrono;
  // std::chrono::milliseconds is an instatiation of std::chrono::duration:
  milliseconds foo (1000); // 1 second
  foo*=60;

  std::cout << "duration (in periods): ";
  std::cout << foo.count() << " milliseconds.\n";

  std::cout << "duration (in seconds): ";
  std::cout << foo.count() * milliseconds::period::num / milliseconds::period::den;
  std::cout << " seconds.\n";

  return 0;
}
```



## 2.Time points

std::chrono::time_point 表示一个具体时间，如上个世纪80年代、你的生日、今天下午、火车出发时间等，只要它能用计算机时钟表示。鉴于我们使用时间的情景不同，这个time point具体到什么程度，由选用的单位决定。一个time point必须有一个clock计时。参见clock的说明。

```
template <class Clock, class Duration = typename Clock::duration>  class time_point;
```

下面是构造使用time_point的例子：

```
// time_point constructors
#include <iostream>
#include <chrono>
#include <ctime>

int main ()
{
  using namespace std::chrono;

  system_clock::time_point tp_epoch;    // epoch value

  time_point <system_clock,duration<int>> tp_seconds (duration<int>(1));

  system_clock::time_point tp (tp_seconds);

  std::cout << "1 second since system_clock epoch = ";
  std::cout << tp.time_since_epoch().count();
  std::cout << " system_clock periods." << std::endl;

  // display time_point:
  std::time_t tt = system_clock::to_time_t(tp);
  std::cout << "time_point tp is: " << ctime(&tt);

  return 0;
}
```

time_point有一个函数time_from_eproch()用来获得1970年1月1日到time_point时间经过的duration。
举个例子，如果timepoint以天为单位，函数返回的duration就以天为单位。

由于各种time_point表示方式不同，chrono也提供了相应的转换函数 time_point_cast。

```
1 template <class ToDuration, class Clock, class Duration>
2   time_point<Clock,ToDuration> time_point_cast (const time_point<Clock,Duration>& tp);
```

比如计算

```
/ time_point_cast
#include <iostream>
#include <ratio>
#include <chrono>

int main ()
{
  using namespace std::chrono;

  typedef duration<int,std::ratio<60*60*24>> days_type;

  time_point<system_clock,days_type> today = time_point_cast<days_type>(system_clock::now());

  std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;

  return 0;
}
```



## 3.Clocks

std::chrono::system_clock 它表示当前的系统时钟，系统中运行的所有进程使用now()得到的时间是一致的。
每一个clock类中都有确定的time_point, duration, Rep, Period类型。
操作有：
now() 当前时间time_point
to_time_t() time_point转换成time_t秒
from_time_t() 从time_t转换成time_point
典型的应用是计算时间日期：

```
// system_clock example
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

int main ()
{
  using std::chrono::system_clock;

  std::chrono::duration<int,std::ratio<60*60*24> > one_day (1);

  system_clock::time_point today = system_clock::now();
  system_clock::time_point tomorrow = today + one_day;

  std::time_t tt;

  tt = system_clock::to_time_t ( today );
  std::cout << "today is: " << ctime(&tt);

  tt = system_clock::to_time_t ( tomorrow );
  std::cout << "tomorrow will be: " << ctime(&tt);

  return 0;
}
```

std::chrono::steady_clock 为了表示稳定的时间间隔，后一次调用now()得到的时间总是比前一次的值大（这句话的意思其实是，如果中途修改了系统时间，也不影响now()的结果），每次tick都保证过了稳定的时间间隔。

操作有：
now() 获取当前时钟
典型的应用是给算法计时：

```
// steady_clock example
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

int main ()
{
  using namespace std::chrono;

  steady_clock::time_point t1 = steady_clock::now();

  std::cout << "printing out 1000 stars...\n";
  for (int i=0; i<1000; ++i) std::cout << "*";
  std::cout << std::endl;

  steady_clock::time_point t2 = steady_clock::now();

  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

  std::cout << "It took me " << time_span.count() << " seconds.";
  std::cout << std::endl;

  return 0;
}
```

最后一个时钟，std::chrono::high_resolution_clock 顾名思义，这是系统可用的最高精度的时钟。实际上high_resolution_clock只不过是system_clock或者steady_clock的typedef。
操作有：
now() 获取当前时钟。