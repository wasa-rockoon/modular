'use strick';

const POLLING_FREQ = 1

let index = -1;

let rocket_packets = {};
let launcher_packets = {};
let gs_packets = {};

const command_format = {
  'B': {
    name: 'Battery',
    entries: {
      'P': { name: 'Vpp', unit: 'V', datatype: 'float', normal: 9.00 },
      'C': { name: 'Vcc', unit: 'V', datatype: 'float', normal: 5.00 },
      'D': { name: 'Vdd', unit: 'V', datatype: 'float', normal: 3.30 },
      'c': { name: 'Vcc', unit: 'A', datatype: 'float' },
      'd': { name: 'Vdd', unit: 'A', datatype: 'float' },
    }
  },
  'P': {
    name: 'GPS',
    entries: {
      'O': { name: 'Longitude', unit: '°', datatype: 'float' },
      'A': { name: 'Latitude',  unit: '°', datatype: 'float' },
      'H': { name: 'Altitude',  unit: 'm', datatype: 'float' },
      'T': { name: 'Time',      unit: 's', datatype: 'time' },
    }
  },
  'S': {
    name: 'LoRa TX',
    entries: {
      'C': { name: 'Code', unit: '', datatype: 'int' },
    }
  },
  'R': {
    name: 'LoRa RX',
    entries: {
      'R': { name: 'RSSI', unit: 'dBm', datatype: 'int' },
    }
  },
  'Sample': {
    name: 'Sample',
    entries: {
      'P': { name: 'Vpp', unit: 'V', datatype: 'float', normal: 9.0 },
      'C': { name: 'Vcc', unit: 'V', datatype: 'float', normal: 5.0 },
      'D': { name: 'Vdd', unit: 'V', datatype: 'float', normal: 3.3 },
      'c': { name: 'Vcc', unit: 'A', datatype: 'float', },
      'd': { name: 'Vdd', unit: 'A', datatype: 'float', },
    }
  },
}

function main() {
  setInterval(fetch, 1000 / POLLING_FREQ);

  $('#connection-error').hide();

  let sample_format = command_format['Sample'];
  let sample = { name: sample_format.name, id: 'S', to: 'G', from: 'G',
                 size: 5, date: new Date(), entries: []};
  for (let k in sample_format.entries) {
    let entry = {};
    Object.assign(entry, sample_format.entries[k]);
    entry.payload = Math.random();
    sample.entries.push(entry)
  }
  console.log(sample);
  // gs_packets['Sample'] = sample;

  render();
}

function fetch() {
  // gs_packets['Sample'].updated = true;

  for (let id in rocket_packets) {
    rocket_packets[id].updated = false;
  }
  for (let id in launcher_packets) {
    launcher_packets[id].updated = false;
  }
  for (let id in gs_packets) {
    gs_packets[id].updated = false;
  }

  console.log('fetch', index);

  $.ajax({
    url: '/data',
    type: 'GET',
    data: { index: index },
    dataType: 'text',
    async: true,
    cache: false,
    timeout: 1000 / POLLING_FREQ}).then((str) => {
    $('#connection-error').hide();

    const lines = str.split('\n').filter(line => line != "");
    index += lines.length;
    const commands = lines.map(parseCommandHex);

    for (let command of commands) {
      console.log(command);
      command.updated = true;
      command.date = new Date();
      switch (command.from) {
      case 'R':
        rocket_packets[command.id] = command;
        break;
      case 'L':
        launcher_packets[command.id] = command;
        break;
      default:
        gs_packets[command.id] = command;
        break;
      }
    }

    render();
  }).catch((e) => {
    $('#connection-error').show();
    console.error(e);
    render();
  })
}

function render() {
  $('#rocket-packets').empty();
  for (let id in rocket_packets) {
    $('#rocket-packets').append(commandItem(rocket_packets[id]));
  }
  $('#launcher-packets').empty();
  for (let id in launcher_packets) {
    $('#launcher-packets').append(commandItem(launcher_packets[id]));
  }
  $('#gs-packets').empty();
  for (let id in gs_packets) {
    $('#gs-packets').append(commandItem(gs_packets[id]));
  }
}

function commandItem(command) {
  return `<table class="pure-table pure-table-horizontal command
                         ${command.updated ? 'updated' : ''}">
            <thead>
               <tr>
                 <th>${command.name}</th>
                 <th>${command.from} to ${command.to}</th>
                 <th>${command.date.toLocaleTimeString('ja-JP')}</th>
               </tr>
            </thead>
            ${command.entries.map(entryItem).join('\n')}
          </table>`
}
function entryItem(entry) {
  let payload = entry.payload;
  if (entry.datatype == 'float')
    payload = entry.payload.toFixed(7);
  else if (entry.datatype == 'time')
    payload = payload.toLocaleTimeString('ja-JP');

  let normal = entry.normal;
  if (normal && entry.datatype == 'float') normal = normal.toFixed(4);

  return `<tr>
            <td>${entry.name} [${entry.unit}]</td>
            <td>${payload}</td>
            <td>${normal ? ('(' + normal + ')') : ''}</td>
          </tr>`
}

function parseCommandHex(line) {
  const hexes = line.replace(/\r?\n/g, '').match(/.{2}/g);
  const bytes = hexes.map(hex => parseInt(hex, 16));

  const id = String.fromCharCode(bytes[1]);
  const to = String.fromCharCode(bytes[2]);
  const from = String.fromCharCode(bytes[3]);
  const size = bytes[4];

  const format = command_format[id];
  let command = {id: id, to: to, from: from, size: size,
                 name: format && format.name,
                 hex: line,
                 entries: []}

  let i = 5;
  while (true) {
    if (i >= bytes.length) break;

    const type = String.fromCharCode(bytes[i] & 0b01111111);

    let entry = {type: type};

    if (format && format.entries[type]) {
      Object.assign(entry, format.entries[type]);
    }
    else {
      entry.name = type;
    }


    if (bytes[i] & 0b10000000) {
      i += 1;
    }
    else {
      let buf = new ArrayBuffer(4);
      let view = new DataView(buf);
      for (let n = 0; n < 4; n++) {
        view.setUint8(3 - n, bytes[i + n + 1]);
      }

      if (format && format.entries[type]) {
        switch (format.entries[type].datatype) {
        case 'float':
          entry.payload = view.getFloat32(0);
          break;
        case 'int':
          entry.payload = view.getInt32(0);
          break;
        case 'time':
          entry.payload = new Date(view.getUint32(0) * 1000);
          break;
        default:
          entry.payload = line.slice(i * 2 + 2, i * 2 + 12);
          break;
        }
      }
      else {
        entry.payload = line.slice(i * 2 + 2, i * 2 + 12);
      }

      i += 5;
    }

    command.entries.push(entry);
  }

  return command;
}


window.addEventListener('load', main);

