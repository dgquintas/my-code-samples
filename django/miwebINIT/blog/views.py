# Create your views here.

from miweb.blog.models import Entry, Comment
from tagging.models import TaggedItem
from django.shortcuts import get_object_or_404, render_to_response
from django.http import HttpResponseRedirect, HttpResponsePermanentRedirect
from django.core.urlresolvers import reverse
from django.core.paginator import Paginator
from miweb.blog.akismet.akismet import Akismet
from miweb import deploy

ak = Akismet(deploy.AKISMET_API_KEY, blog_url='http://www.ptrtovoid.net')

def entry(request, year, month, day, slug):
  entry = get_object_or_404(Entry, slug=slug, pub_date__year=year,
      pub_date__month=month, pub_date__day=day,)
  comments = entry.comment_set.filter(is_spam=False).order_by('when')
#  all_entries = Entry.objects.all().filter(published=True).order_by('-pub_date')

  return render_to_response('blog/entry_blog.html', 
      {'entry':entry, 
       'comments':comments,
#       'all_entries': all_entries
      } 
      )

def list(request, page=1, tag=None):
  page = int(page)

  entries = Entry.objects.all().filter(published=True).order_by('-pub_date')
  if tag:
    entries = TaggedItem.objects.get_by_model(entries, tag)
  
  p = Paginator(entries, 5).page(page)

  return render_to_response('blog/base_blog.html',
      { 'entries': p.object_list,
#        'all_entries': entries,
        'tag': tag,
        'older_page': p.next_page_number() if p.has_next() else None,
        'newer_page': p.previous_page_number() if p.has_previous() else None } )
      
def comment(request):
  fields = request.POST

  parent_post = Entry.objects.get(pk=fields['entry-id'])

  akismetData = {}
  akismetData['user_ip'] = request.META['REMOTE_ADDR']
  akismetData['user_agent'] = request.META['HTTP_USER_AGENT']
  akismetData['referrer'] = request.META['HTTP_REFERER']
  akismetData['comment_type'] = 'comment'
  akismetData['comment_author'] = fields['who']

  what = fields['what'].encode('ascii', 'ignore')

  is_spam = ak.comment_check(what, akismetData)

  new_comment = Comment(entry = parent_post,
      who = fields['who'],
      what = fields['what'],
      is_spam = is_spam)
  new_comment.save()

  post_url = "%s#%s%d" % (parent_post.get_absolute_url(), Comment.COMMENT_ANCHOR, new_comment.id)

  return HttpResponseRedirect( post_url )


