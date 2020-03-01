# Refraction
用C++实现 《重构 改善既有代码的设计 第2版》

## 第一章 重构，第一个实例

背景：剧院请剧团演出。客户（剧院）会指定几出剧目，而剧团则根据观众人数以及剧目类型像客户（剧院）收费。剧目类型分两种：喜剧、悲剧。另外，再给客户（剧院）发出张丹时，还会根据观众人给出客户（剧院）“观众量积分”（volume credt）优惠，下次再请该剧团表演时可以用到。

剧目：

```
{
	"hamlet": {"name": "Hamlet", "type": "tragedy"},
	"as-like": {"name": "As You Like It", "type": "comedy"},
	"othello": {"name": "Othello", "type": "tragedy"}
}
```

单据：

```
{
	"customer" : "BigCo",
	"performances" : 
	[
		{
			"audience" : 55,
			"playID" : "hamlet"
		},
		{
			"audience" : 35,
			"playID" : "as-like"
		},
		{
			"audience" : 40,
			"playID" : "othello"
		}
	]
}
```

前提：[用C++读取Json](https://www.jianshu.com/p/e0c1f3fdf6f9)

下面这个简单的函数用以打印账单详情（钱币单位做了简化）

```cpp
void statement(Json::Value& invoice, Json::Value& plays)
{
    cout << "\n========" << "print statement" << "========" << endl;
    int totalAmount = 0;
    int volumeCredits = 0;
    cout << "Statement for : " << invoice["customer"].asString() << endl;

    for (Json::Value& perf : invoice["performances"]) {
        Json::Value& play = plays[perf["playID"].asString()];
        int thisAmount = 0;
        if (!strcmp(play["type"].asString().c_str(), "tragedy"))
        {
            thisAmount = 400;
            if (perf["audience"].asInt() > 30) {
                thisAmount += 10 * (perf["audience"].asInt() - 30);
            }
        }
        else if (!strcmp(play["type"].asString().c_str(), "comedy"))
        {
            thisAmount = 300;
            if (perf["audience"].asInt() > 20) {
                thisAmount += 100 + 5 * (perf["audience"].asInt() - 20);
            }
            thisAmount += 3 * perf["audience"].asInt();
        }
        else
        {
            cout << "ERROR" << endl;;
        }

        // add volume credits
        volumeCredits += max((perf["audience"].asInt() -  30), 0);
        // add extra credit for every ten comedy attendees
        if ("comedy" ==  play["type"].asString()) volumeCredits += floor(perf["audience"].asInt()/5);
        // print line for this order
        printf("    %s: %d (%d seats)\n", play["name"].asString().c_str(), thisAmount, perf["audience"].asInt());
        totalAmount += thisAmount;
    }
    printf("Amount owed is %d\n", totalAmount );
    printf("You earned %d credits\n", volumeCredits);
}
```

## 注

### Json读取代码

[用C++读取Json](https://www.jianshu.com/p/e0c1f3fdf6f9)

```cpp
bool jsonReader(string& path, Json::Value& root)
{
    ifstream is(path, ios::binary);
    if (!is.is_open())
    {
        cout << "open json file failed." << endl;
        return false;
    }

    JSONCPP_STRING errs;
    Json::CharReaderBuilder readerBuilder;

    bool result = Json::parseFromStream(readerBuilder, is, &root, &errs);
    if (!result || !errs.empty()) {
        cout << "parseJson err. " << errs << endl;
        is.close();
        return false;
    }
    is.close();
    return true;
}
```

