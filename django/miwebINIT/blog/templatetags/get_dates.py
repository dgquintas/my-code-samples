from django.template import Library, Node, TemplateSyntaxError
from miweb.blog.models import Entry

register = Library()

class DatesNode(Node):
  def __init__(self, time_unit, varname):
    self.time_unit = time_unit
    self.varname = varname

  def render(self, context):
    context[self.varname] = Entry.objects.filter(published=True).dates('pub_date', self.time_unit, 'DESC')
    return ''

@register.tag
def get_dates(parser, token):
  bits = token.contents.split()
  if len(bits) != 4:
    raise TemplateSyntaxError, "get_dates tag takes exactly four argument"
  if bits[2] != 'as':
    raise TemplateSyntaxError, "second argument to get_dates tag must be 'as'"

  return DatesNode(bits[1], bits[3])





