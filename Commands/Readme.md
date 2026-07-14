<h2>JOIN Command</h2>

<h3>1. Creating a New Channel</h3>

<p align="center">
  <img src="images/join-new-channel.png" alt="Join New Channel" width="900">
</p>

<p align="center">
  <b>Figure 1.</b> Client joins a channel that does not exist. The server creates the channel, assigns the first client as the channel operator, and adds the channel to the server.
</p>

<br>

<h3>2. Joining an Existing Channel</h3>

<p align="center">
  <img src="images/join-existing-channel.png" alt="Join Existing Channel" width="900">
</p>

<p align="center">
  <b>Figure 2.</b> Client joins an existing channel after the server validates membership requirements (invite-only, password, user limit, etc.).
</p>

<h2>PRIVMSG Command (Private Message)</h2>

<p>
The <code>PRIVMSG</code> command allows a client to send a private message
directly to another connected user.
The server first searches for the target nickname.
If the nickname exists, the message is forwarded to the recipient.
Otherwise, the sender receives the IRC numeric reply
<code>401 ERR_NOSUCHNICK</code>.
</p>

<h3>PRIVMSG to a User</h3>

<p align="center">
    <img src="images/privmsg-private-message.png"
         alt="PRIVMSG to User Flow"
         width="1000">
</p>

<p align="center">
<b>Figure.</b>
Flow of the <code>PRIVMSG</code> command when sending a private message to a user.
The server parses the command, searches for the target nickname,
returns <code>401 ERR_NOSUCHNICK</code> if the user does not exist,
or forwards the message to the destination client if the user is found.
</p>

<h2>PRIVMSG Command (Channel Message)</h2>

<p>
The <code>PRIVMSG</code> command can also be used to send a message to an IRC
channel. The server first checks whether the target channel exists. If the
channel does not exist, the sender receives
<code>401 ERR_NOSUCHNICK</code>. If the channel exists but the client is not a
member, the server returns <code>404 ERR_CANNOTSENDTOCHAN</code>. Otherwise,
the server broadcasts the message to every member of the channel except the
sender.
</p>

<h3>PRIVMSG to a Channel</h3>

<p align="center">
    <img src="images/privmsg-channel.png"
         alt="PRIVMSG to Channel Flow"
         width="1000">
</p>

<p align="center">
<b>Figure.</b>
Flow of the <code>PRIVMSG</code> command when sending a message to an IRC
channel. The server validates the channel, checks whether the sender is a
member, returns the appropriate IRC error replies when necessary, or
broadcasts the message to all channel members except the sender.
</p>