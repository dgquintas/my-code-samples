from django.template import Library, Node, TemplateSyntaxError
from miweb.blog.models import Entry
from django.db.models import get_model

register = Library()

class LatestNode(Node):
  def __init__(self, model, num, varname):
    self.num = num
    self.varname = varname
    self.model = get_model(*model.split('.'))

  def render(self, context):
    context[self.varname] = self.model._default_manager.all()[:self.num]
    return ''

@register.tag
def get_latest(parser, token):
  bits = token.contents.split()
  if len(bits) != 5:
    raise TemplateSyntaxError, "get_latest tag takes exactly five argument"
  if bits[3] != 'as':
    raise TemplateSyntaxError, "second argument to get_latest tag must be 'as'"

  return LatestNode(bits[1], bits[2], bits[4])





