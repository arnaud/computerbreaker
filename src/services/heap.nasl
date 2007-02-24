# This file is part of the Computer Breaker project.
#
#    Computer Breaker is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    Computer Breaker is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Computer Breaker; if not, write to the Free Software
#    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

if(description)
{
script_id(6666669);
script_version("$Revision: 1.0 $");

name["english"] = "Server Heap Overflow Bug";

script_name(english:name["english"]);

desc["english"] = "
";

script_description(english:desc["english"]);

summary["english"] = "";

script_summary(english:summary["english"]);

script_category(ACT_GATHER_INFO);

script_copyright(english:"This script is under no Copyright at all");

family["english"] = "Annoy your favorite neighbour";
script_family(english:family["english"]);
script_dependencie("http_version.nasl");
script_require_ports(44211);
exit(0);
}



port = get_kb_item("Services/tanned");
if(!port)port = 44211;
if(!get_port_state(port))exit(0);

soc = open_sock_tcp(port);
if(!soc)exit(0);

security_hole(port);
