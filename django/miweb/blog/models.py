from django.db import models
from tagging.fields import TagField
from tagging.models import Tag
from django.conf import settings
import datetime
#from blog.template_utils.markup import formatter
import markdown

def process_markdown(srctxt, images):
  md = markdown.Markdown()
  image_ref = "\n"
  for image in images:
    image_url = image.image.url
    image_ref = '%s\n[%s]: %s "%s"' % (image_ref, image.name, image_url, image.description)

  srctxt += image_ref
  return  md.convert(srctxt)


class BodyCache(models.Model):
  value = models.TextField(blank=True)
  last_update = models.DateTimeField(default=datetime.datetime.min)

  def __unicode__(self):
    return u'For entry %s (slug)' % (self.entry.slug,)

class Entry(models.Model):
  title = models.CharField(max_length=128)
  snip = models.CharField(max_length=64)
  slug = models.SlugField(unique_for_date='pub_date', 
      help_text="Automatically built from title")
  tags = TagField()
  pub_date = models.DateTimeField('Date Published',
      default=datetime.datetime.now)
  last_update = models.DateTimeField('Last Update Date',
      default=datetime.datetime.now, editable=False)
  body = models.TextField('Entry body')
  published = models.BooleanField(default=False)
  images = models.ManyToManyField('Image', blank=True)
  links = models.ManyToManyField('Link', blank=True)

  cached_body = models.OneToOneField(BodyCache, null=True, blank=True)

  def __unicode__(self):
    return u'%s' % (self.title,)


  @property #lazy
  def body_html(self):
    if self.cached_body.last_update < self.last_update:
      self.cached_body.value = process_markdown(self.body, self.images.all())
      self.cached_body.last_update = datetime.datetime.now()
      self.cached_body.save()

    return self.cached_body.value


  @models.permalink
  def get_absolute_url(self):
    return ('blog-entry', (),
        {'year': self.pub_date.year,
         'month': self.pub_date.date().strftime("%m"),
         'day': self.pub_date.date().strftime("%d"),
         'slug': self.slug,
        })

  def get_previous_published(self):
    return self.get_previous_by_pub_date(published=True)

  def get_next_published(self):
    return self.get_next_by_pub_date(published=True)

  def get_tags(self):
    return Tag.objects.get_for_object(self)

  def get_all_comments(self):
    return self.comment_set.all()

  def get_comments(self):
    return self.comment_set.filter(is_spam=False)

  def get_num_comments(self):
    return self.comment_set.filter(is_spam=False).count()

  def save(self):
    if not self.cached_body:
      bc = BodyCache()
      bc.save()
      self.cached_body = bc

    self.last_update = datetime.datetime.now()
    super(Entry, self).save()


  class Meta:
    verbose_name_plural = "Entries"
    ordering = ('-pub_date',)
    get_latest_by = 'pub_date'



class Image(models.Model):
  name = models.CharField(max_length=100 , unique=True)
  description = models.CharField(max_length=256)
  __upload_to_path = 'uploads/%s/%%Y/%%b/%%d/' % (settings.DATABASE_USER,)
  image = models.ImageField( upload_to=__upload_to_path)

  def __unicode__(self):
    return self.name

class Link(models.Model):
  name = models.CharField(max_length=100)
  description = models.CharField(max_length=256)
  url = models.URLField()

  def __unicode__(self):
    return u'Link. %s: (%s)' % (self.name, self.url)


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


  
