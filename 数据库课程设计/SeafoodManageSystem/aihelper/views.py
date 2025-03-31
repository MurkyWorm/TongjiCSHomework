from django.shortcuts import render, redirect
from user.models import User
import erniebot, json
from jsonschema import validate
import pymysql

class PromptJson:
	def __init__(self, rulers) -> None:
		self.rulers_str = '请根据下面的scheame描述生成给定格式json,只返回json数据,并且只返回其中的properties数据,不要其他内容。'
		self.scheame_str = ''
		self.example_str = ''

		self.set_rulers(rulers)
		self.set_scheame(self.json_obj())
		self.set_example(self.example())

	def json_obj(self):
		return '''```{'type':'string'}```'''

	def example(self):
		return '正确的示例如下：'
	def __call__(self, *args, **kwargs):
		pass
    
	def set_scheame(self, json_obj):
		json_str = str(json_obj).replace(' ', '').replace('\n', '').replace('\t', '')
		json_str = '```' + json_str + '```'
		self.scheame_str = json_str

	def set_example(self, example_str:str):
		example_str = example_str.replace(' ', '').replace('\n', '').replace('\t', '')
		self.example_str = example_str

	def set_rulers(self, rulers):
		self.rulers_str = rulers.replace(' ', '').replace('\n', '').replace('\t', '')

	def __str__(self) -> str:
		return self.__repr__()
	
	def __repr__(self) -> str:
		return self.rulers_str + self.scheame_str + self.example_str

    
class SQLPrompt(PromptJson):
    def __init__(self) -> None:
        rulers = '''你是数据库查询程序，需要根据描述生成对应的json结果，结果是查询的一些属性和条件，如果有对应的描述就写入对应位置。
                    严格按照下面的scheame描述生成给定格式json，只返回json数据，并且只返回其中的properties数据,不要其他内容:
                '''
        super().__init__(rulers)

    def json_obj(self)->dict:
        schema_attr = {'type': 'object', 
                'properties':{
                    'table': {'enum':['oceannuclearpollution', 'product'], 'description': '表的名称，查询污染是oceannuclearpollution，查询水产品是product'},
                    'pollution_select_type': {'enum':['time', 'location'], 'description': '查询的表是oceannuclearpollution时的查询类型，time是按时间查询，location是按地点查询'},
                    'pollution_date': {"type": 'string', "format": "date", 'description': '根据日期查询污染时对应的时间'},
                    'lat': {"type": 'number', 'description': '根据地点查询污染的纬度'},
                    'lng': {"type": 'number', 'description': '根据地点查询污染的经度'},
                    'product_name': {"type": 'string', 'description': '查询产品时产品的名字'},
                    'product_state': {"type": 'boolean', 'description': '水产品未售出为假，售出为真'},
                    'product_date': {"type": 'string', "format": "date", 'description': '查询水产品时对应的日期'},
                    'product_date_compare': {'enum':['=', '>', '<'], 'description': '查询水产品时对应的日期描述，在某一天为=，某一天之后为>，某一天之前为<'}
                    },
                "additionalProperties": False
            }
        return schema_attr
        
        def example(self)->str:
            example = '''正确的示例如下：
                        查询维度为21.5，经度为144.7位置处的污染情况: ```{'table': 'oceannuclearpollution', 'pollution_select_type': 'location', 'lat': 21.5, 'lng': 144.7}```,
                        查询2024年6月14日的污染情况: ```{'table': 'oceannuclearpollution', 'pollution_select_type': 'time', 'pollution_date': '2024-06-14'}``` ,
                        查询叫蛏子的水产品: ```{'table': 'product', 'product_name': '蛏子'}``` 。
                        查询2024年6月14日生产的水产品: ```{'table': 'product', 'product_state': '2024-06-14', 'product_date_compare': '='}``` ,
                        查询2024年3月1日之后生产的售出水产品: ```{'table': 'product', 'product_state': '2024-03-01', 'product_state': False', product_date_compare': '>'}``` ,

                    '''
            return example
	
class ErnieBotWrap():

	def __init__(self):
		erniebot.api_type = 'aistudio'
		erniebot.access_token = '5a21ce71f98fb6870adeb0d57142ae0fce2eeb81'
		self.msgs = []
		self.model = 'ernie-3.5'
		self.prompt_str = '请根据下面的描述生成给定格式json'

	@staticmethod
	def get_mes(role, dilog):
		data = {}
		if role == 0:
			data['role'] = 'user'
		elif role ==1:
			data['role'] = 'assistant'
		data['content'] = dilog	
		return data

	def set_promt(self, prompt_str):
		self.prompt_str = prompt_str


	def get_res(self, str_input, record=False, request_timeout=5):
		if len(str_input)<1:
			return False, None
		start_str = " ```"
		end_str = " ```, 根据这段描述生成给定格式json"
		str_input = start_str + str_input + end_str
		msg_tmp = self.get_mes(0, str_input)
		if record:
			self.msgs.append(msg_tmp)
			msgs = self.msgs
		else:
			msgs = [msg_tmp]
		try:
			response = erniebot.ChatCompletion.create(model=self.model, messages=msgs, system=self.prompt_str, top_p=0.1,
											_config_=dict(api_type="AISTUDIO",), request_timeout=request_timeout)
		except Exception as e:
			return False, None
		str_res = response.get_result()
		if record:
			self.msgs.append(self.get_mes(1, str_res))
		return True, str_res
	
	@staticmethod
	def get_json_str(json_str:str):
		try:
			index_s = json_str.find("```json") + 7
		except Exception as e:
			index_s = 0
		try:
			index_e = json_str[index_s:].find("```") + index_s
		except Exception as e:
			index_e = len(json_str)
		import json
		msg_json = json.loads(json_str[index_s:index_e])
		return msg_json
	
	def get_res_json(self, str_input, record=False, request_timeout=10):
		state, str_res = self.get_res(str_input, record, request_timeout)
		if state:
			obj_json = self.get_json_str(str_res)
			return obj_json
		else:
			return None


def helperpage(request):
    if request.session.get('is_login', None):
        user_name = request.session['user_name']
        user = User.objects.get(user_name=user_name)
        identity = user.identity
    else:
        return redirect('/user/login/')
    display = [0, 0, 0]
    cities_count = []
    date_count = []
    products = []
    return render(request, 'helperpage.html', {'identity': identity, 'display': display, 'cities_count': cities_count, 'date_count': date_count, 'products': products, 'last_question': ""})

def select_info(request):
    if request.session.get('is_login', None):
        user_name = request.session['user_name']
        user = User.objects.get(user_name=user_name)
        identity = user.identity
    else:
        return redirect('/user/login/')
        

    display = [0, 0, 0]
    points = []
    date_count = []
    products = []
    

    ernie = ErnieBotWrap()
    ernie.set_promt(str(SQLPrompt()))
    query = request.POST.get('query')
    if len(query) > 1:
        json_res = ernie.get_res_json(query)
        if json_res['properties']['table'] == 'oceannuclearpollution':
            table_name = "home_oceannuclearpollution"
            fields = "*"
            if json_res['properties']['pollution_select_type'] == 'time':
                restriction = "date=" + "'" + json_res['properties']['pollution_date'] + "'"
                display[0] = 1
                sql = "SELECT " + fields + " FROM " + table_name + " WHERE " + restriction + ";"
            else:
                lat = int(float(json_res['properties']['lat']) / 2) * 2
                lng = int(float(json_res['properties']['lng']) / 2) * 2
                restriction = "lat=" + str(lat) + " and lng=" +  str(lng)
                display[1] = 1
                sql = "SELECT " + fields + " FROM " + table_name + " WHERE " + restriction + " ORDER BY date;"
            
        else:
            table_name = "seafood_product"
            fields = "product_id, class_name, quantity, lat, lng, production_time, expiration_time, state"
            display[2] = 1
            if 'product_name' in json_res['properties']:
                restriction1 = "class_name=" + "'" + json_res['properties']['product_name'] + "'"
            else:
                restriction1 = ""
            if 'product_state' in json_res['properties']:
                restriction2 = "state=" + str(int(json_res['properties']['product_state']))
            else:
                restriction2 = ""
            if 'product_date' in json_res['properties']:
                restriction3 = "DATE(production_time)" + json_res['properties']['product_date_compare'] + json_res['properties']['product_date']
            else:
                restriction3 = ""
            sql = "SELECT " + fields + " FROM " + table_name + " WHERE"
            is_void = True
            if restriction1 != "":
                sql = sql + " " + restriction1
                is_void = False
            if restriction2 != "":
                if is_void == False:
                    sql = sql + " AND"
                sql = sql + " " + restriction2
                is_void = False
            if restriction3 != "":
                if is_void == False:
                    sql = sql + " AND"
                sql = sql + " " + restriction3
            sql = sql + " ORDER BY production_time DESC;"
            
        print(sql)

        config = {
            'host': 'localhost',  # 数据库服务器地址
            'user': 'wenxin',  # 数据库用户名
            'password': 'c.r/2003',  # 数据库密码
            'database': 'seafoodmanagesystem',  # 数据库名
            'charset': 'utf8mb4',  # 字符编码
            'cursorclass': pymysql.cursors.DictCursor  # 使用字典游标，便于读取列名
        }
        connection = pymysql.connect(**config)
        try:
            with connection.cursor() as cursor:
                cursor.execute(sql)
                results = cursor.fetchall()
                if display[0]:
                    points = results
                elif display[1]:
                    date_count = results[:10]
                elif display[2]:
                    products = results[:300]
        finally:
            connection.close()
    
    last_question = query

    
    return render(request, 'helperpage.html', {'identity': identity, 'display': display, 'points': points, 'date_count': date_count, 'products': products, 'last_question': last_question})