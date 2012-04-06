from django.http import Http404, HttpResponse
from django.shortcuts import render_to_response
import datetime

def hello(request):
  return HttpResponse("Foobarismo!")

def display_meta(request):
  html = []
        
  httpstuff = filter(  
      lambda (k,v): k.startswith('HTTP'), 
      request.META.iteritems() 
      )
  map( 
      lambda (k,v): html.append('<tr><td>%s</td><td>%s</td></tr>' % (k,v)), 
      httpstuff 
      )
  res = '<table border="1">%s</table>' % ('\n'.join(html))
  return HttpResponse(res)
    

def current_datetime(request):
  current_date = datetime.datetime.now()
  return render_to_response('current_datetime.html', locals())

def hours_ahead(request, hour_offset):
  try:
    hour_offset = int(hour_offset)
  except ValueError:
    raise Http404()
  now = datetime.datetime.now()
  td = datetime.timedelta(hours=hour_offset)
  next_time = now + td

  return render_to_response('offset_datetime.html', locals())
