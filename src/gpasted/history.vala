/*
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *	Copyright 2011 Marc-Antoine Perennou <Marc-Antoine@Perennou.com>
 *
 *	This file is part of GPaste.
 *
 *	GPaste is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	GPaste is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with GPaste.  If not, see <http://www.gnu.org/licenses/>.
 */

namespace GPaste {

    [DBus (name = "org.gnome.GPaste")]
    interface GPasteBusSignalClient : Object {
        public abstract void notify_change() throws IOError;
    }

    public class History : Object {
        private List<string> _history;
        public List<string> history {
            get {
                return get_unowned_history();
            }
        }

        private static History _instance;
        public static History instance {
            get {
                if (_instance == null)
                    _instance = new History();
                return _instance;
            }
        }

        private GPasteBusSignalClient _gpaste_signal;
        private GPasteBusSignalClient gpaste_signal {
            get {
                if (_gpaste_signal == null) {
                    try {
                        _gpaste_signal = Bus.get_proxy_sync(BusType.SESSION, "org.gnome.GPaste", "/org/gnome/GPaste");
                    } catch (IOError e) {
                        stderr.printf(_("Couldn't conext to self bus to notify for changes.\n"));
                    }
                }
                return _gpaste_signal;
            }
        }

        private unowned List<string> get_unowned_history() {
            return _history;
        }

        public virtual signal void changed() {
            save();
            if (gpaste_signal != null) {
                try {
                    gpaste_signal.notify_change();
                } catch (IOError e) {
                    stdout.printf(_("Couldn't notify change via DBus.\n"));
                }
            }
        }

        private History() {
            _history = new List<string>();
        }

        public void add(string selection) {
            for (unowned List<string?> s = history ; s != null ; s = s.next) {
                if (s.data == selection) {
                    _history.remove_link(s);
                    break;
                }
            }
            _history.prepend(selection);
            if (_history.length() > GPastedSettings.maxHistorySize()) {
                unowned List<string?> tmp = history;
                for (int i = 0 ; i < GPastedSettings.maxHistorySize() ; ++i)
                    tmp = tmp.next;
                do {
                    unowned List<string?> next = tmp.next;
                    _history.remove_link(tmp);
                    tmp = next;
                } while(tmp != null);
            }
            changed();
        }

        public void select(uint index) {
            if (index >= _history.length()) return;
            string selection = _history.nth_data(index);
            add(selection);
            ClipboardsManager.instance.select(selection);
        }

        public void load() {
            string history_dir_path = Environment.get_user_data_dir() + "/gpaste";
            var history_dir = File.new_for_path(history_dir_path);
            if (!history_dir.query_exists()) {
                stderr.printf(_("Could not read history file\n"));
                Posix.mkdir(history_dir_path, 0700);
                return;
            }
            var history_file = File.new_for_path(history_dir_path + "/history");
            if (!history_file.query_exists()) {
                stderr.printf(_("Could not read history file\n"));
                return;
            }

            try {
                int64 length;
                var dis = new DataInputStream(history_file.read());
                while((length = dis.read_int64()) != 0) {
                    var line = new StringBuilder();
                    for(int64 i = 0 ; i < length ; ++i) line.append_unichar(dis.read_byte());
                    _history.append(line.str);
                }
            } catch (Error e) {
                stderr.printf(_("Could not read history file\n"));
            }
        }

        public void save() {
            var history_file = File.new_for_path(Environment.get_user_data_dir() + "/gpaste/history");
            try {
                if (history_file.query_exists())
                    history_file.delete();
                var history_file_stream = history_file.create(FileCreateFlags.NONE);
                if (!history_file.query_exists()) {
                    stderr.printf(_("Could not create history file\n"));
                    return;
                }
                var dos = new DataOutputStream(history_file_stream);
                foreach(string line in _history) {
                    dos.put_int64(line.length);
                    dos.put_string(line);
                }
                dos.put_int64(0);
            } catch (Error e) {
                stderr.printf(_("Could not create history file\n"));
            }
        }
    }

}

