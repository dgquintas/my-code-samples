import direct.directbase.DirectStart
from pandac.PandaModules import *

from direct.task import Task
from direct.actor import Actor
from direct.interval.IntervalGlobal import *
import math

#load the 1st environment model
environ = loader.loadModel("models/environment")
environ.reparentTo(render)
environ.setScale(0.25,0.25, 0.25)
environ.setPos(-8,42,0)

#task to move the camera
def SpinCameraTask(task):
  angledegrees = task.time * 6.0
  angleradiants = angledegrees * (math.pi / 180.0)
  base.camera.setPos(20*math.sin(angleradiants), 
                     -20.0*math.cos(angleradiants),3)
  base.camera.setHpr(angledegrees, 0, 0)
  return Task.cont

#taskMgr.add(SpinCameraTask, "SpinCameraTask")


#load the panda actor, and loop its animation
pandaActor = Actor.Actor("models/panda-model", {"walk":"models/panda-walk4"})
pandaActor.setScale(0.005, 0.005, 0.005)
pandaActor.reparentTo(render)
pandaActor.loop("walk")

#create the four lerp intervals needed to walk back and forth
pandaPosInerval1 = pandaActor.posInterval(13, Point3(0,-10, 0), startPos=Point3(0,10,0))
pandaPosInerval2 = pandaActor.posInterval(13, Point3(0,10, 0), startPos=Point3(0,-10,0))
pandaHprInerval1 = pandaActor.hprInterval(3, Point3(180,0, 0), startHpr=Point3(0,0,0))
pandaHprInerval2 = pandaActor.hprInterval(3, Point3(0,0, 0), startHpr=Point3(180,0,0))


#create and play the sequence that coordinates the intervals
pandaPace = Sequence(pandaPosInerval1, pandaHprInerval1, 
    pandaPosInerval2, pandaHprInerval2, name = "pandaPace")
pandaPace.loop()
run()
