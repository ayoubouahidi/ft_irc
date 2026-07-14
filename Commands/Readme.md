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

<h2>TOPIC Command (Read Topic)</h2>

<p>
The <code>TOPIC</code> command allows a client to retrieve the current topic of
an IRC channel. The server first verifies that the requested channel exists and
that the client is a member of that channel. If these checks succeed, the server
returns either the current topic or indicates that no topic has been set.
</p>

<h3>Reading a Channel Topic</h3>

<p align="center">
    <img src="images/topic-read-flow.png"
         alt="TOPIC Read Command Flow"
         width="1000">
</p>

<p align="center">
<b>Figure.</b>
Execution flow of the <code>TOPIC #channel</code> command. The server searches
for the requested channel, verifies that the client belongs to it, and then
returns one of the following replies:
<code>403 ERR_NOSUCHCHANNEL</code> if the channel does not exist,
<code>442 ERR_NOTONCHANNEL</code> if the client is not a member,
<code>331 RPL_NOTOPIC</code> if no topic has been set, or
<code>332 RPL_TOPIC</code> containing the current channel topic.
</p>


<h2>TOPIC Command (Update Topic)</h2>

<p>
The <code>TOPIC</code> command can also be used to modify the topic of an IRC
channel by providing a new topic. Before updating the topic, the server verifies
that the channel exists, the client is a member of the channel, and—if topic
protection (<code>+t</code>) is enabled—that the client has operator
privileges. After a successful update, the server broadcasts the new topic to
all channel members.
</p>

<h3>Updating a Channel Topic</h3>

<p align="center">
    <img src="images/topic-update-flow.png"
         alt="TOPIC Update Command Flow"
         width="1000">
</p>

<p align="center">
<b>Figure.</b>
Execution flow of the
<code>TOPIC #channel :&lt;new topic&gt;</code> command. The server first checks
whether the channel exists and whether the client belongs to it. If topic
protection (<code>+t</code>) is enabled, only channel operators are allowed to
change the topic; otherwise, any channel member may update it. After the topic
is successfully changed, the server broadcasts the
<code>TOPIC</code> message to every member of the channel so that all clients
immediately receive the updated topic.
</p>


<h2>INVITE Command</h2>

<p>
The <code>INVITE</code> command allows a client to invite another user to join
a specific IRC channel. Before sending the invitation, the server validates
that the target user exists, the channel exists, the sender is a member of the
channel, the target user is not already inside the channel, and—if the channel
is invite-only (<code>+i</code>)—that the sender has operator privileges.
After all validations succeed, the target user is added to the channel's invite
list, the invitation is delivered to the target, and the sender receives a
confirmation reply.
</p>

<h3>Inviting a User to a Channel</h3>

<p align="center">
    <img src="images/invite-command.png.png"
         alt="INVITE Command Flow"
         width="1000">
</p>

<p align="center">
<b>Figure.</b>
Execution flow of the
<code>INVITE &lt;nickname&gt; &lt;channel&gt;</code> command. The server first
checks that all required parameters are present, then verifies that the target
user and channel exist. It ensures the sender is a member of the channel, the
target user is not already inside it, and—if invite-only mode
(<code>+i</code>) is enabled—that the sender is a channel operator. When all
checks succeed, the target user is added to the channel's invite list, the
server sends the invitation message to the target user, and finally replies
with <code>341 (RPL_INVITING)</code> to confirm that the invitation was
successfully sent.
</p>