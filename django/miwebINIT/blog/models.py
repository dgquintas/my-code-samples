from django.db import models
from tagging.fields import TagField
from tagging.models import Tag
import datetime
from blog.template_utils.markup import formatter


class Entry(models.Model):
  title = models.CharField(max_length=128)
  snip = models.CharField(max_length=64)
  slug = models.SlugField(unique_for_date='pub_date', 
      help_text="Automatically built from title")
  tags = TagField()
  pub_date = models.DateTimeField('Date Published',
      default=datetime.datetime.now)
  body = models.TextField('Entry body')
  body_html = models.TextField('Entry body as HTML', blank=True, null=True)
  published = models.BooleanField(default=False)

  def __unicode__(self):
    return u'%s' % (self.title,)

  @models.permalink
  def get_absolute_url(self):
    return ('blog-entry', (),
        {'year': self.pub_date.year,
         'month': self.pub_date.date().strftime("%m"),
         'day': self.pub_date.date().strftime("%d"),
         'slug': self.slug,
        })

  def get_previous_published(self):
    return self.get_previous_by_pub_date()

  def get_next_published(self):
    return self.get_next_by_pub_date()

  def get_tags(self):
    return Tag.objects.get_for_object(self)

  def save(self):
    self.body_html = formatter(self.body)

    super(Entry, self).save()


  class Meta:
    verbose_name_plural = "Entries"
    ordering = ('-pub_date',)
    get_latest_by = 'pub_date'



class Comment(models.Model):
  entry = models.ForeignKey(Entry)
  who = models.CharField('Commenter', blank=False, null=False, 
      max_length=40)
  what = models.TextField('Comment', blank=False, null=False)
  when = models.DateTimeField(default=datetime.datetime.now)
  is_spam = models.BooleanField(default=False)
  COMMENT_ANCHOR = "comment-"

  def get_absolute_url(self):
    return self.entry.get_absolute_url() + '#' + Comment.COMMENT_ANCHOR + str(self.id)

  def __unicode__(self):
    return u'%s on %s' % (self.who, self.entry.title)



  
