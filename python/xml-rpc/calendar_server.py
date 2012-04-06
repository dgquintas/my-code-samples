import calendar, SimpleXMLRPCServer

#The server object
class Calendar:
    def getMonth(self, year, month):
        return calendar.month(year, month)

    def getYear(self, year):
        return calendar.calendar(year)


calendar_object = Calendar()
server = SimpleXMLRPCServer.SimpleXMLRPCServer(("localhost", 1234))
server.register_instance(calendar_object)

#Go into the main listener loop
print "Listening on port 1234"
server.serve_forever()
