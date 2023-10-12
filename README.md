# qtrest-example
Full functionality example application for Qt REST library (https://github.com/kafeg/qtrest)

This sample APP uses the next Backend sample as reference: https://github.com/qtrest/qtrest-example-backend/

In this example application you will found example C++ and QML code for working with API methods of http://skid.kz site.

I will use it's REST API, who folows HATEOAS (https://github.com/yiisoft/yii2/blob/master/docs/guide/rest-quick-start.md):
- GET /coupons: list all coupons page by page;
- GET /coupons/1: return the details of the coupon 1.

## Building

```
0. Minimal Qt version is Qt 5.7
1. Install qpm from http://qpm.io
2. git clone https://github.com/kafeg/qtrest-example.git
3. cd qtrest-example
4. lrelease qtrest-example.pro
5. git submodule init
6. git submodule update
7. qmake
8. make
```

## Testing

You may for example test this API by using those headers:
- Accept: application/json
- Authorization: Bearer 8aef452ee3b32466209535b96d456b06

Be careful: my server is still small =)

For example: curl -H "Accept: application/json" -H "Authorization: Bearer 8aef452ee3b32466209535b96d456b06" http://api.skid.kz/v1/coupon?fields=id,title,sourceServiceId,imagesLinks,mainImageLink,pageLink,cityId,boughtCount&sort=-id,title&isArchive=0

Will return headers:
```
Server: nginx
Date: Sun, 28 Feb 2016 11:49:34 GMT
Content-Type: application/json; charset=UTF-8
Transfer-Encoding: chunked
Connection: keep-alive
Keep-Alive: timeout=60
X-Pagination-Total-Count: 7719
X-Pagination-Page-Count: 386
X-Pagination-Current-Page: 1
X-Pagination-Per-Page: 20
Link: <http://api.skid.kz/v1/coupon?fields=id%2Ctitle%2CsourceServiceId%2CimagesLinks%2CmainImageLink%2CpageLink%2CcityId%2CboughtCount&sort=-id%2Ctitle&isArchive=0&page=1>; rel=self,
<http://api.skid.kz/v1/coupon?fields=id%2Ctitle%2CsourceServiceId%2CimagesLinks%2CmainImageLink%2CpageLink%2CcityId%2CboughtCount&sort=-id%2Ctitle&isArchive=0&page=2>; rel=next,
<http://api.skid.kz/v1/coupon?fields=id%2Ctitle%2CsourceServiceId%2CimagesLinks%2CmainImageLink%2CpageLink%2CcityId%2CboughtCount&sort=-id%2Ctitle&isArchive=0&page=386>; rel=last
```
And body:
```
{
  {
    "id": 24957
    "sourceServiceId": 1
    "cityId": 1
    "title": "Салон красоты Vitality"
    "imagesLinks": {
      0:  "https://static.chocolife.me/static/upload/images/deal/for_deal_page/28000/27418/660x305/2_201602261123514564646959.jpg"
      1:  "https://static.chocolife.me/static/upload/images/deal/for_deal_page/28000/27418/660x305/3_201602261123614564646968353.jpg"
      2:  "https://static.chocolife.me/static/upload/images/deal/for_deal_page/28000/27418/660x305/4_20160226112111456464911014.jpg"
      3:  "https://static.chocolife.me/static/upload/images/deal/for_deal_page/28000/27418/660x305/5_201602261121914564649197072.jpg"
      4:  "https://static.chocolife.me/static/upload/images/deal/for_deal_page/28000/27418/310x240/1_20160226112361456464696371.jpg"
    }
    "mainImageLink": "https://static.chocolife.me/static/upload/images/deal/for_deal_page/28000/27418/310x240/1_20160226112361456464696371.jpg"
    "boughtCount": "0"
    "pageLink": "https://ala.chocolife.me/27418-salon-krasotyvitality/"
    "serviceName": "Chocolife.me"
    "cityName": "Алматы"
  },
  {
    "id": 24956
    "sourceServiceId": 1
    "cityId": 1
    "title": "Салон красоты Vitality"
    "imagesLinks": {
      0:  "https://static.chocolife.me/static/upload/images/deal/for_deal_page/28000/27417/660x305/2_201602261024414564599644154.jpg"
      1:  "https://static.chocolife.me/static/upload/images/deal/for_deal_page/28000/27417/660x305/3_201602261020014564599803748.jpg"
      2:  "https://static.chocolife.me/static/upload/images/deal/for_deal_page/28000/27417/660x305/4_201602261025914564599799436.jpg"
      3:  "https://static.chocolife.me/static/upload/images/deal/for_deal_page/28000/27417/660x305/5_201602261024514564599651143.jpg"
      4:  "https://static.chocolife.me/static/upload/images/deal/for_deal_page/28000/27417/310x240/1_201602261025914564599791696.jpg"
    }
    "mainImageLink": "https://static.chocolife.me/static/upload/images/deal/for_deal_page/28000/27417/310x240/1_201602261025914564599791696.jpg"
    "boughtCount": "0"
    "pageLink": "https://ala.chocolife.me/27417-salon-krasoty-vitality/"
    "serviceName": "Chocolife.me"
    "cityName": "Алматы"
  },
  ...
}
```
## Screenshots
![Qt Micro REST Client Framework](https://raw.githubusercontent.com/kafeg/qtrest-example/master/assets/images/example1.png "REST API Qt example 1")
![Qt Micro REST Client Framework](https://raw.githubusercontent.com/kafeg/qtrest-example/master/assets/images/example2.png "REST API Qt example 2")
![Qt Micro REST Client Framework](https://raw.githubusercontent.com/kafeg/qtrest-example/master/assets/images/example3.png "REST API Qt example 3")
