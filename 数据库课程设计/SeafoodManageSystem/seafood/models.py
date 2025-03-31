from django.db import models

class Product(models.Model):
    # 水产产品的唯一标识
    product_id = models.AutoField(primary_key=True)
    # 水产的种类，使用汉字描述
    class_name = models.CharField(max_length=50)
    # 水产的质量，单位是kg
    quantity = models.FloatField()
    # 产地的经度
    lat = models.FloatField()
    # 产地的纬度
    lng = models.FloatField()
    # 生产者的身份证号
    producer = models.CharField(max_length=20)
    # 生产时间
    production_time = models.DateTimeField()
    # 过期时间
    expiration_time = models.DateTimeField()
    # 水产的状态，使用整数表示，0和1分别代表未售出和已售出
    state = models.IntegerField(choices=((0, '未售出'), (1, '已售出')))
