# Create your views here.

from django.shortcuts import render_to_response, get_object_or_404
from django.http import HttpResponseRedirect
from django.core.urlresolvers import reverse
from mysite.polls.models import Poll, Choice

#def index(request):
#  latest_poll_list = Poll.objects.all().order_by('-pub_date')[:5]
#  return render_to_response('polls/index.html', 
#      {'latest_poll_list': latest_poll_list})
#
#def detail(request, poll_id):
#  p = get_object_or_404(Poll, pk=poll_id)
#  return render_to_response('polls/detail.html', {'poll':p})

def vote(request, poll_id):
  p = get_object_or_404(Poll, pk=poll_id)
  try:
    selected_choice = p.choice_set.get(pk=request.POST['choice'])
  except (KeyError, Choice.DoesNotExist):
    #redisplay the poll voting form
    return render_to_response('polls/poll_detail.html', {
      'object': p,
      'error_message': "no seleccionaste una opcion, payaso",
      })
  else:
    selected_choice.votes += 1
    selected_choice.save()
    # Always return an HttpResponseRedirect after successfully dealing
    # with POST data. This prevents data from being posted
    # twice if a user hits the Back button.
    return HttpResponseRedirect(reverse('poll_results', args=(p.id,)))

#def results(request, poll_id):
#  p = get_object_or_404(Poll, pk=poll_id)
#  return render_to_response('polls/results.html', {'poll':p})
