from django.shortcuts import render
from django.http import JsonResponse
from django.http import HttpResponseRedirect
from .models import User_info
from INTERACT.models import Creation, Like, Dislike, coll
from django.forms.models import model_to_dict
import ast
from django.db.models import Q
from Levenshtein import ratio
import random
from django.views.decorators.csrf import csrf_protect

@csrf_protect
# Create your views here.
def home_user(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            user_info1 = User_info.objects.filter(user_name=decoded_name).first()
            user_info = model_to_dict(user_info1)
            user_data = {}
            user_data['id'] = user_info['id']
            user_data['user_pp'] = user_info['user_pp'] + '.jpg'
            user_data['user_name'] = user_info['user_name']
            user_data['user_ideas'] = user_info['user_ideas']
            user_data['user_echo'] = user_info['user_echo']
            user_data['user_fan'] = user_info['user_fan']
            user_data['user_like'] = user_info['user_like']
            user_data['user_reply'] = user_info['user_reply']
            user_data['user_concen'] = user_info['user_concen']
            user_data['user_coll'] = user_info['user_coll']
            user_data['user_generate'] = user_info['user_generate']
            if 'choice' in request.GET:
                user_data['choice'] = request.GET['choice']
            else:
                user_data['choice'] = 'all'
            if 'value' in request.GET:
                user_data['value'] = request.GET['value']
            else:
                user_data['value'] = 1
            return render(request, './HOME.html', user_data)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def home_articles(request):
    decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
    articles = []
    count = 0
    i = 0
    if request.GET['choice'] == 'all' or request.GET['choice'] == 'search':
        creations = Creation.objects.filter(is_punish='已发布')
        for creation in creations:
            if request.GET['choice'] == 'search':
                similarity = ratio(request.GET['value'], creation.title)
                if similarity < 0.7:
                    continue
            elif request.GET['choice'] == 'all':
                i = i + 1
                if count > 5:
                    break
                random_number = random.randint(-1, 1)
                if creation.like + creation.dislike == 0:
                    random_number = random_number
                else:
                    random_number = random_number + creation.like / (creation.like + creation.dislike)
                if random_number < (creations.count() - i)/creations.count():
                    continue
                count = count + 1
            mid = ['', '', '', '', '', '', '', '', '', '', '']
            if len(creation.title) > 10:
                mid[0] = creation.title[:10] + '..'
            else:
                mid[0] = creation.title
            mid[1] = creation.user_name
            if len(creation.introd_cont) > 50:
                mid[2] = creation.introd_cont[:50] + '..'
            else:
                mid[2] = creation.introd_cont
            mid[3] = creation.look
            mid[4] = creation.like
            mid[5] = creation.dislike
            mid[6] = creation.comment
            mid[7] = creation.id
            likes = Like.objects.filter(Q(target=creation.id) & Q(user_name=decoded_name))
            if likes.count() == 0:
                mid[8] = 'black'
            else:
                mid[8] = 'green'
            dislikes = Dislike.objects.filter(Q(target=creation.id) & Q(user_name=decoded_name))
            if dislikes.count() == 0:
                mid[9] = 'black'
            else:
                mid[9] = 'red'
            colls = coll.objects.filter(Q(creation_name=creation.id) & Q(user_name=decoded_name))
            if colls.count() == 0:
                mid[10] = 'black'
            else:
                mid[10] = 'green'
            articles.append(mid)
    elif request.GET['choice'] == 'coll':
        cos = coll.objects.filter(user_name=decoded_name)
        for co in cos:
            creations = Creation.objects.filter(id=co.creation_name)
            if creations.count() == 0:
                continue
            else:
                creation = creations.first()
            mid = ['', '', '', '', '', '', '', '', '', '', '']
            if len(creation.title) > 10:
                mid[0] = creation.title[:10] + '..'
            else:
                mid[0] = creation.title
            mid[1] = creation.user_name
            if len(creation.introd_cont) > 50:
                mid[2] = creation.introd_cont[:50] + '..'
            else:
                mid[2] = creation.introd_cont
            mid[3] = creation.look
            mid[4] = creation.like
            mid[5] = creation.dislike
            mid[6] = creation.comment
            mid[7] = creation.id
            likes = Like.objects.filter(Q(target=creation.id) & Q(user_name=decoded_name))
            if likes.count() == 0:
                mid[8] = 'black'
            else:
                mid[8] = 'green'
            dislikes = Dislike.objects.filter(Q(target=creation.id) & Q(user_name=decoded_name))
            if dislikes.count() == 0:
                mid[9] = 'black'
            else:
                mid[9] = 'red'
            colls = coll.objects.filter(Q(creation_name=creation.id) & Q(user_name=decoded_name))
            if colls.count() == 0:
                mid[10] = 'black'
            else:
                mid[10] = 'green'
            articles.append(mid)
    return JsonResponse(articles, safe=False)

def home_exit(request):
    response = HttpResponseRedirect('/REG_LOG/log')
    response.set_cookie('is_login', 'false', expires='Thu, 01 Jan 1970 00:00:00 GMT')
    return response

def my_blocks_user(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            user_info1 = User_info.objects.filter(user_name=decoded_name).first()
            user_info = model_to_dict(user_info1)
            user_data = {}
            user_data['id'] = user_info['id']
            user_data['user_pp'] = user_info['user_pp'] + '.jpg'
            user_data['user_name'] = user_info['user_name']
            user_data['user_ideas'] = user_info['user_ideas']
            user_data['user_echo'] = user_info['user_echo']
            user_data['user_fan'] = user_info['user_fan']
            user_data['user_like'] = user_info['user_like']
            user_data['user_reply'] = user_info['user_reply']
            user_data['user_concen'] = user_info['user_concen']
            user_data['user_coll'] = user_info['user_coll']
            user_data['user_generate'] = user_info['user_generate']
            return render(request, './MY_BLOCKS.html', user_data)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def user_articles(request):
    articles = []
    decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
    creations = Creation.objects.filter(user_name=decoded_name)
    for creation in creations:
        mid = ['', '', '', '', '', '', '', '', '', '', '']
        if len(creation.title) > 10:
            mid[0] = creation.title[:10] + '..'
        else:
            mid[0] = creation.title
        mid[1] = creation.user_name
        if len(creation.introd_cont) > 50:
            mid[2] = creation.introd_cont[:50] + '..'
        else:
            mid[2] = creation.introd_cont
        mid[3] = creation.look
        mid[4] = creation.like
        mid[5] = creation.dislike
        mid[6] = creation.comment
        mid[7] = creation.id
        likes = Like.objects.filter(Q(target=creation.id) & Q(user_name=decoded_name))
        if likes.count() == 0:
            mid[8] = 'black'
        else:
            mid[8] = 'green'
        dislikes = Dislike.objects.filter(Q(target=creation.id) & Q(user_name=decoded_name))
        if dislikes.count() == 0:
            mid[9] = 'black'
        else:
            mid[9] = 'red'
        colls = coll.objects.filter(Q(creation_name=creation.id) & Q(user_name=decoded_name))
        if colls.count() == 0:
            mid[10] = 'black'
        else:
            mid[10] = 'green'
        articles.append(mid)
    return JsonResponse(articles, safe=False)