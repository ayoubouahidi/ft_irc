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